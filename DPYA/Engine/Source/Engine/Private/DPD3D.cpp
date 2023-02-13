
#include "DPD3D.h"

#include "DPCore.h"
#include "DPMesh.h"


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

bool DPD3D::Initialize(HWND HWnd, const unsigned int InWidth, const unsigned int InHeight)
{
	ScreenWidth = InWidth;
	ScreenHeight = InHeight;

	HRESULT HResult;

	// Create D3D11 Device and Context
	{
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
	}

	// Create Render Target
	{
		ID3D11Texture2D* FrameBuffer;
		HResult = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);
		if (FAILED(HResult))
		{
			if (nullptr != FrameBuffer)
			{
				FrameBuffer->Release();
				return false;
			}
		}

		HResult = Device->CreateRenderTargetView(FrameBuffer, NULL, &RenderTargetView);
		if (FAILED(HResult))
		{
			if (nullptr != FrameBuffer)
			{
				FrameBuffer->Release();
				return false;
			}
		}

		FrameBuffer->Release();
	}

	// Create Vertex Shader and Pixel Shader
	ID3DBlob* VSBlob;
	{
		ID3DBlob* ShaderErrorBlob;
		HResult = D3DCompileFromFile(L"Engine/Shader/VSShader.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &VSBlob, &ShaderErrorBlob);
		if (FAILED(HResult))
		{
			const char* errorString = NULL;
			if (HResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
				errorString = "Could not compile shader; file not found";
			else if (ShaderErrorBlob) {
				errorString = (const char*)ShaderErrorBlob->GetBufferPointer();
				ShaderErrorBlob->Release();
			}
			MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
			return false;
		}

		HResult = Device->CreateVertexShader(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), nullptr, &VertexShader);

		if (FAILED(HResult)) 
		{
			if (nullptr != ShaderErrorBlob)
				ShaderErrorBlob->Release();
			if (nullptr != VSBlob)
				VSBlob->Release();
			return false;
		}

		ID3DBlob* PSBlob;
		HResult = D3DCompileFromFile(L"Engine/Shader/PSShader.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &PSBlob, &ShaderErrorBlob);
		if (FAILED(HResult))
		{
			const char* errorString = NULL;
			if (HResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
				errorString = "Could not compile shader; file not found";
			else if (ShaderErrorBlob) {
				errorString = (const char*)ShaderErrorBlob->GetBufferPointer();
				ShaderErrorBlob->Release();
			}
			MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
			return false;
		}

		HResult = Device->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), nullptr, &PixelShader);
		if (FAILED(HResult))
		{
			if (nullptr != ShaderErrorBlob)
				ShaderErrorBlob->Release();
			if (nullptr != VSBlob)
				VSBlob->Release();
			if (nullptr != PSBlob)
				PSBlob->Release();
			return false;
		}

		PSBlob->Release();
	}

	// Create Input Layout
	{
		D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		HResult = Device->CreateInputLayout(LayoutDesc, ARRAYSIZE(LayoutDesc), VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), &InputLayout);
		if (FAILED(HResult))
		{
			if (nullptr != VSBlob)
				VSBlob->Release();
			return false;
		}

		VSBlob->Release();
	}

	{
		D3D11_VIEWPORT Viewport;
		Viewport.TopLeftX = 0.0f;
		Viewport.TopLeftY = 0.0f;
		Viewport.Width = static_cast<float>(ScreenWidth);
		Viewport.Height = static_cast<float>(ScreenHeight);
		Viewport.MinDepth = 0.0f;
		Viewport.MaxDepth = 1.0f;

		DeviceContext->RSSetViewports(1, &Viewport);
	}

	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);

	DeviceContext->IASetInputLayout(InputLayout);

	DeviceContext->VSSetShader(VertexShader, nullptr, 0);
	DeviceContext->PSSetShader(PixelShader, nullptr, 0);

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

	//DeviceContext->PSSetShaderResources();

	// Bind the render target view and depth stencil buffer to the output render pipeline.
	/*DeviceContext->OMSetRenderTargets(1, &RenderTargetView, 0);*/

	ProjectionTM = DirectX::XMFLOAT4X4{ Matrix4x4::ScaleMatrix(fabsf(InWidth*0.5f), fabsf(InHeight*0.5f)).ToFloats() };


	return true;
}

void DPD3D::ClearView()
{
	float color[4] = { 0.1f, 0.9f, 0.6f, 1.0f };  //{ 0.0f, 0.2f, 0.5f, 1.0f };
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

	DeviceContext->IASetPrimitiveTopology(InTopology);

	// Create Vertex Buffer
	ID3D11Buffer* VertexBuffer;
	{
		D3D11_BUFFER_DESC VertexBufferDesc;
		ZeroMemory(&VertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
		VertexBufferDesc.ByteWidth = sizeof(VertexData) * Vertices.Num();
		VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA VertexSubresourceData;
		ZeroMemory(&VertexSubresourceData, sizeof(D3D11_SUBRESOURCE_DATA));
		VertexSubresourceData.pSysMem = Vertices.Get();
		VertexSubresourceData.SysMemPitch = 0;
		VertexSubresourceData.SysMemSlicePitch = 0;

		HResult = Device->CreateBuffer(&VertexBufferDesc, &VertexSubresourceData, &VertexBuffer);
		if (FAILED(HResult))
		{
			if (nullptr != VertexBuffer)
				VertexBuffer->Release();
			return false;
		}
	}

	ID3D11Buffer* IndexBuffer;
	{
		D3D11_BUFFER_DESC IndexBufferDesc;
		ZeroMemory(&IndexBufferDesc, sizeof(D3D11_BUFFER_DESC));
		IndexBufferDesc.ByteWidth = sizeof(unsigned int) * Indices.Num();
		IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		//IndexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA IndexSubresourceData;
		IndexSubresourceData.pSysMem = Indices.Get();
		IndexSubresourceData.SysMemPitch = 0;
		IndexSubresourceData.SysMemSlicePitch = 0;

		HResult = Device->CreateBuffer(&IndexBufferDesc, &IndexSubresourceData, &IndexBuffer);
		if (FAILED(HResult))
		{
			if (nullptr != IndexBuffer)
				IndexBuffer->Release();
			return false;
		}
	}

	UINT Stride = sizeof(VertexData);
	UINT Offset = 0;
	DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer, &Stride, &Offset);
	DeviceContext->IASetIndexBuffer(IndexBuffer, DXGI_FORMAT_R32_UINT, Offset);

	VertexBuffer->Release();
	IndexBuffer->Release();

	DeviceContext->DrawIndexed(Indices.Num(), 0, 0);

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

