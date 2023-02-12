
#include "DPCore.h"
#include "DPD3D.h"

struct HLSLBuffer
{
	DirectX::XMFLOAT4X4 ModelMatrix;
	DirectX::XMFLOAT4X4 ViewMatrix;
	DirectX::XMFLOAT4X4 ProjectionMatrix;
};

DPD3D* DPD3D::Instance = nullptr;

DPD3D::DPD3D()
	: Device(nullptr)
	, DeviceContext(nullptr)
	, RenderTargetView(nullptr)
	, VertexShader(nullptr)
	, PixelShader(nullptr)
	, InputLayout(nullptr)
	, ConstantBuffer(nullptr)
	, TextureView(nullptr)
	, Texture(nullptr)
	, SwapChain(nullptr)
{ }

DPD3D::~DPD3D()
{
	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}

	if (nullptr != DeviceContext)
	{
		DeviceContext->Release();
		DeviceContext = nullptr;
	}
	
	if (nullptr != RenderTargetView)
	{
		RenderTargetView->Release();
		RenderTargetView = nullptr;
	}

	if (nullptr != VertexShader)
	{
		VertexShader->Release();
		VertexShader = nullptr;
	}

	if (nullptr != PixelShader)
	{
		PixelShader->Release();
		PixelShader = nullptr;
	}

	if (nullptr != InputLayout)
	{
		InputLayout->Release();
		InputLayout = nullptr;
	}

	if (nullptr != ConstantBuffer)
	{
		ConstantBuffer->Release();
		ConstantBuffer = nullptr;
	}

	if (nullptr != TextureView)
	{
		TextureView->Release();
		TextureView = nullptr;
	}

	if (nullptr != Texture)
	{
		Texture->Release();
		Texture = nullptr;
	}

	if (nullptr != SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	Instance = nullptr;
}

// this function initializes and prepares Direct3D for use
bool DPD3D::Initialize(HWND HWnd, const float InWidth, const float InHeight)
{
	HRESULT HResult;

	// Create SwapChain and Device
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferDesc.Width = 0;
	SwapChainDesc.BufferDesc.Height = 0;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.OutputWindow = HWnd;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = 0;
	
	D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	
	HResult = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, FeatureLevels, ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION, &SwapChainDesc, &SwapChain, &Device, NULL, &DeviceContext);
	if (FAILED(HResult))
	{
		return false;
	}

	// Create BackBuffer -----------------------------------------------------------------------------------
	ID3D11Texture2D* BackBufferPtr;
	HResult = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBufferPtr);
	if (FAILED(HResult))
	{
		if (nullptr != BackBufferPtr)
			BackBufferPtr->Release();

		return false;
	}

	// Create the render target view with the back buffer pointer.
	HResult = Device->CreateRenderTargetView(BackBufferPtr, NULL, &RenderTargetView);
	if (FAILED(HResult))
	{
		if (nullptr != BackBufferPtr)
			BackBufferPtr->Release();

		return false;
	}

	BackBufferPtr->Release();

	// Set Vertex & Pixel Shader --------------------------------------------------------------------------- 
	ID3D10Blob *VSBlob, *PSBlob, *ErrorBlob;
	HResult = D3DCompileFromFile(L"Engine/Shader/VSShader.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &VSBlob, &ErrorBlob);
	if (FAILED(HResult))
	{
		SafeDelete(VSBlob);
		SafeDelete(ErrorBlob);
		return false;
	}
	HResult = Device->CreateVertexShader(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), NULL, &VertexShader);
	if (FAILED(HResult))
	{
		SafeDelete(VSBlob);
		SafeDelete(ErrorBlob);
		return false;
	}
	HResult = D3DCompileFromFile(L"Engine/Shader/PSShader.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &PSBlob, &ErrorBlob);
	if (FAILED(HResult))
	{
		SafeDelete(VSBlob);
		SafeDelete(PSBlob);
		SafeDelete(ErrorBlob);
		return false;
	}
	HResult = Device->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), NULL, &PixelShader);
	if (FAILED(HResult))
	{
		SafeDelete(VSBlob);
		SafeDelete(PSBlob);
		SafeDelete(ErrorBlob);
		return false;
	}

	// create input layout object
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	HResult = Device->CreateInputLayout(layout, ARRAYSIZE(layout), VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), &InputLayout);
	if (FAILED(HResult))
	{
		return false;
	}

	/*DeviceContext->IASetInputLayout(InputLayout);*/

	VSBlob->Release(); PSBlob->Release();

	//DeviceContext->VSSetShader(VertexShader, 0, 0);
	//DeviceContext->PSSetShader(PixelShader, 0, 0);

	// Create Constant Buffer (Matrix) --------------------------------------------------------------------
	//D3D11_BUFFER_DESC ConstantDesc;
	//ZeroMemory(&ConstantDesc, sizeof(D3D11_BUFFER_DESC));
	//ConstantDesc.Usage = D3D11_USAGE_DYNAMIC;
	//ConstantDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//ConstantDesc.ByteWidth = sizeof(HLSLBuffer);
	//ConstantDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//HResult = Device->CreateBuffer(&ConstantDesc, nullptr, &ConstantBuffer);
	//if (FAILED(HResult))
	//{
	//	return false;
	//}

	//// Load Default Texture -------------------------------------------------------------------------------
	//Device->CreateShaderResourceView();

	//// Sampler (UV) ---------------------------------------------------------------------------------------
	//Device->CreateSamplerState();
	//DeviceContext->PSSetSamplers();

	//// Set Blend State ------------------------------------------------------------------------------------
	//Device->CreateBlendState();
	//DeviceContext->OMSetBlendState();

	// Set Viewport ----------------------------------------------------------------------------------------
	D3D11_VIEWPORT Viewport;
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;
	Viewport.Width = (float)InWidth;
	Viewport.Height = (float)InHeight;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;


	// Create the viewport.
	//DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	DeviceContext->RSSetViewports(1, &Viewport);
	//DeviceContext->PSSetShaderResources();

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	/*DeviceContext->OMSetRenderTargets(1, &RenderTargetView, 0);*/


	ProjectionTM = DirectX::XMFLOAT4X4{ Matrix4x4::ScaleMatrix(fabsf(InWidth*0.5f), fabsf(InHeight*0.5f)).ToFloats() };


	return true;
}

void DPD3D::ClearView()
{
	float color[4] = { 0.0f, 0.2f, 0.5f, 1.0f };
	DeviceContext->ClearRenderTargetView(RenderTargetView, color);
}
bool DPD3D::PresentView()
{
	HRESULT HResult = SwapChain->Present(1, 0);
	if (FAILED(HResult))
	{
		return false;
	}

	return true;
}

bool DPD3D::Draw(const Matrix4x4& ModelMatrix, const Matrix4x4& ViewMatrix, const DPArray<VertexData>& Vertices, const DPArray<unsigned int>& Indices, D3D11_PRIMITIVE_TOPOLOGY InTopology)
{
	HRESULT HResult;

	ID3D11Buffer* VertexBuffer;

	D3D11_BUFFER_DESC VertexDesc;
	ZeroMemory(&VertexDesc, sizeof(D3D11_BUFFER_DESC));
	VertexDesc.Usage = D3D11_USAGE_DEFAULT;
	VertexDesc.ByteWidth = sizeof(VertexData) * Vertices.Num();
	VertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//VertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA VertexData;
	VertexData.pSysMem = Vertices.Get();
	VertexData.SysMemPitch = 0;
	VertexData.SysMemSlicePitch = 0;

	HResult = Device->CreateBuffer(&VertexDesc, &VertexData, &VertexBuffer);
	if (FAILED(HResult))
	{
		if (nullptr != VertexBuffer)
			VertexBuffer->Release();

		return false;
	}

	//ID3D11Buffer* IndexBuffer;

	//D3D11_BUFFER_DESC IndexDesc;
	//ZeroMemory(&IndexDesc, sizeof(D3D11_BUFFER_DESC));
	//IndexDesc.Usage = D3D11_USAGE_DEFAULT;
	//IndexDesc.ByteWidth = sizeof(unsigned int)*3;
	//IndexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	////IndexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//unsigned int* trialIndex = new unsigned int[3]{ 0, 1, 2 };
	//D3D11_SUBRESOURCE_DATA IndexData;
	//IndexData.pSysMem = trialIndex;
	//IndexData.SysMemPitch = 0;
	//IndexData.SysMemSlicePitch = 0;

	//HResult = Device->CreateBuffer(&IndexDesc, &IndexData, &IndexBuffer);
	//if (FAILED(HResult))
	//{
	//	return false;
	//}

	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, 0);
	DeviceContext->IASetPrimitiveTopology(InTopology);
	DeviceContext->IASetInputLayout(InputLayout);

	DeviceContext->VSSetShader(VertexShader, 0, 0);
	DeviceContext->PSSetShader(PixelShader, 0, 0);

	UINT Stride = sizeof(VertexData);
	UINT Offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offset);
	//DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, Offset);

	DeviceContext->Draw(Vertices.Num(), 0);

	return true;
}

DPD3D* DPD3D::Get()
{
	if (nullptr == Instance)
	{
		Instance = new DPD3D();
	}
	return Instance;
}

