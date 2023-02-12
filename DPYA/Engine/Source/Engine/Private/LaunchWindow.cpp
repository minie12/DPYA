
#include <windows.h>

#include "DPEngine.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include <assert.h>

#include "DPMesh.h"

//static bool global_windowDidResize = false;
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
//{
//	LRESULT result = 0;
//	switch (msg)
//	{
//	case WM_KEYDOWN:
//	{
//		if (wparam == VK_ESCAPE)
//			DestroyWindow(hwnd);
//		break;
//	}
//	case WM_DESTROY:
//	{
//		PostQuitMessage(0);
//		break;
//	}
//	case WM_SIZE:
//	{
//		global_windowDidResize = true;
//		break;
//	}
//	default:
//		result = DefWindowProcW(hwnd, msg, wparam, lparam);
//	}
//	return result;
//}

int WINAPI WinMain(HINSTANCE HInstance, HINSTANCE HPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//HWND hwnd;
	//{
	//	WNDCLASSEXW winClass = {};
	//	winClass.cbSize = sizeof(WNDCLASSEXW);
	//	winClass.style = CS_HREDRAW | CS_VREDRAW;
	//	winClass.lpfnWndProc = &WndProc;
	//	winClass.hInstance = HInstance;
	//	winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
	//	winClass.hCursor = LoadCursorW(0, IDC_ARROW);
	//	winClass.lpszClassName = L"MyWindowClass";
	//	winClass.hIconSm = LoadIconW(0, IDI_APPLICATION);

	//	if (!RegisterClassExW(&winClass)) {
	//		MessageBoxA(0, "RegisterClassEx failed", "Fatal Error", MB_OK);
	//		return GetLastError();
	//	}

	//	RECT initialRect = { 0, 0, 1024, 768 };
	//	AdjustWindowRectEx(&initialRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
	//	LONG initialWidth = initialRect.right - initialRect.left;
	//	LONG initialHeight = initialRect.bottom - initialRect.top;

	//	hwnd = CreateWindowExW(WS_EX_OVERLAPPEDWINDOW,
	//		winClass.lpszClassName,
	//		L"02. Drawing a Triangle",
	//		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	//		CW_USEDEFAULT, CW_USEDEFAULT,
	//		initialWidth,
	//		initialHeight,
	//		0, 0, HInstance, 0);

	//	if (!hwnd) {
	//		MessageBoxA(0, "CreateWindowEx failed", "Fatal Error", MB_OK);
	//		return GetLastError();
	//	}
	//}

	//ID3D11Device* d3d11Device;
	//ID3D11DeviceContext* d3d11DeviceContext;
	//IDXGISwapChain* d3d11SwapChain;


	//// Create D3D11 Device and Context
	//DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	//ZeroMemory(&SwapChainDesc, sizeof(SwapChainDesc));
	//SwapChainDesc.BufferCount = 1;
	//SwapChainDesc.BufferDesc.Width = 0;
	//SwapChainDesc.BufferDesc.Height = 0;
	//SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//SwapChainDesc.OutputWindow = hwnd;
	//SwapChainDesc.SampleDesc.Count = 1;
	//SwapChainDesc.SampleDesc.Quality = 0;
	//SwapChainDesc.Windowed = true;
	//SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	//SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	//SwapChainDesc.Flags = 0;

	//D3D_FEATURE_LEVEL FeatureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	//HRESULT HResult = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, FeatureLevels, ARRAYSIZE(FeatureLevels), D3D11_SDK_VERSION, &SwapChainDesc, &d3d11SwapChain, &d3d11Device, NULL, &d3d11DeviceContext);
	//if (FAILED(HResult))
	//{
	//	return false;
	//}

	//// Create Framebuffer Render Target
	//ID3D11RenderTargetView* d3d11FrameBufferView;
	//{
	//	ID3D11Texture2D* d3d11FrameBuffer;
	//	HRESULT hResult = d3d11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
	//	assert(SUCCEEDED(hResult));

	//	hResult = d3d11Device->CreateRenderTargetView(d3d11FrameBuffer, 0, &d3d11FrameBufferView);
	//	assert(SUCCEEDED(hResult));
	//	d3d11FrameBuffer->Release();
	//}

	//// Create Vertex Shader
	//ID3DBlob* vsBlob;
	//ID3D11VertexShader* vertexShader;
	//{
	//	ID3DBlob* shaderCompileErrorsBlob;
	//	HRESULT hResult = D3DCompileFromFile(L"Engine/Shader/VSShader.hlsl", nullptr, nullptr, "VSMain", "vs_5_0", 0, 0, &vsBlob, &shaderCompileErrorsBlob);
	//	if (FAILED(hResult))
	//	{
	//		const char* errorString = NULL;
	//		if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
	//			errorString = "Could not compile shader; file not found";
	//		else if (shaderCompileErrorsBlob) {
	//			errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
	//			shaderCompileErrorsBlob->Release();
	//		}
	//		MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
	//		return 1;
	//	}

	//	hResult = d3d11Device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);
	//	assert(SUCCEEDED(hResult));
	//}

	//// Create Pixel Shader
	//ID3D11PixelShader* pixelShader;
	//{
	//	ID3DBlob* psBlob;
	//	ID3DBlob* shaderCompileErrorsBlob;
	//	HRESULT hResult = D3DCompileFromFile(L"Engine/Shader/PSShader.hlsl", nullptr, nullptr, "PSMain", "ps_5_0", 0, 0, &psBlob, &shaderCompileErrorsBlob);
	//	if (FAILED(hResult))
	//	{
	//		const char* errorString = NULL;
	//		if (hResult == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
	//			errorString = "Could not compile shader; file not found";
	//		else if (shaderCompileErrorsBlob) {
	//			errorString = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
	//			shaderCompileErrorsBlob->Release();
	//		}
	//		MessageBoxA(0, errorString, "Shader Compiler Error", MB_ICONERROR | MB_OK);
	//		return 1;
	//	}

	//	hResult = d3d11Device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
	//	assert(SUCCEEDED(hResult));
	//	psBlob->Release();
	//}

	//// Create Input Layout
	//ID3D11InputLayout* inputLayout;
	//{
	//	D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	//	{
	//		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	};

	//	HRESULT hResult = d3d11Device->CreateInputLayout(inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
	//	assert(SUCCEEDED(hResult));
	//	vsBlob->Release();
	//}

	//// Create Vertex Buffer
	//ID3D11Buffer* vertexBuffer;
	//UINT numVerts;
	//UINT stride;
	//UINT offset;
	//DPMesh* TMesh;
	//{	
	//	float vertexData[] = { // x, y, r, g, b, a
	//		0.0f,  0.5f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.5f, 0.0f,
	//		0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f,
	//		-0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f
	//	};

	//	DPMesh* TMesh;
	//	TMesh = new DPTriangleMesh();
	//	TMesh->CreateAtCenter(2.f, 2.f, Vector4(0.f, 1.f, 0.f, 0.f));

	//	VertexData* VData = new VertexData[3];
	//	VData[0] = VertexData(Vector3(0.0f, 0.5f, 0.f), Vector4(0.f, 1.f, 0.f, 1.f), Vector2(0.5f, 0.f));
	//	VData[1] = VertexData(Vector3(0.5f, -0.5f, 0.f), Vector4(1.f, 0.f, 0.f, 1.f), Vector2(1.f, 1.f));
	//	VData[2] = VertexData(Vector3(-0.5f, -0.5f, 0.f), Vector4(0.f, 0.f, 1.f, 1.f), Vector2(0.f, 1.f));
	//	
	//	stride = sizeof(VertexData);
	//	numVerts = 3;
	//	offset = 0;

	//	D3D11_BUFFER_DESC vertexBufferDesc = {};
	//	vertexBufferDesc.ByteWidth = sizeof(VertexData) * 3;
	//	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//	D3D11_SUBRESOURCE_DATA vertexSubresourceData = { TMesh->GetVertices().Get() };

	//	HRESULT hResult = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &vertexBuffer);
	//	assert(SUCCEEDED(hResult));
	//}

	//// Main Loop
	//bool isRunning = true;
	//while (isRunning)
	//{
	//	MSG msg = {};
	//	while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
	//	{
	//		if (msg.message == WM_QUIT)
	//			isRunning = false;
	//		TranslateMessage(&msg);
	//		DispatchMessageW(&msg);
	//	}

	//	if (global_windowDidResize)
	//	{
	//		d3d11DeviceContext->OMSetRenderTargets(0, 0, 0);
	//		d3d11FrameBufferView->Release();

	//		HRESULT res = d3d11SwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);
	//		assert(SUCCEEDED(res));

	//		ID3D11Texture2D* d3d11FrameBuffer;
	//		res = d3d11SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);
	//		assert(SUCCEEDED(res));

	//		res = d3d11Device->CreateRenderTargetView(d3d11FrameBuffer, NULL,
	//			&d3d11FrameBufferView);
	//		assert(SUCCEEDED(res));
	//		d3d11FrameBuffer->Release();

	//		global_windowDidResize = false;
	//	}

	//	FLOAT backgroundColor[4] = { 0.1f, 0.9f, 0.6f, 1.0f };
	//	d3d11DeviceContext->ClearRenderTargetView(d3d11FrameBufferView, backgroundColor);

	//	RECT winRect;
	//	GetClientRect(hwnd, &winRect);
	//	D3D11_VIEWPORT viewport = { 0.0f, 0.0f, (FLOAT)(winRect.right - winRect.left), (FLOAT)(winRect.bottom - winRect.top), 0.0f, 1.0f };
	//	d3d11DeviceContext->RSSetViewports(1, &viewport);

	//	d3d11DeviceContext->OMSetRenderTargets(1, &d3d11FrameBufferView, nullptr);

	//	d3d11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//	d3d11DeviceContext->IASetInputLayout(inputLayout);

	//	d3d11DeviceContext->VSSetShader(vertexShader, nullptr, 0);
	//	d3d11DeviceContext->PSSetShader(pixelShader, nullptr, 0);

	//	d3d11DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	//	d3d11DeviceContext->Draw(numVerts, 0);

	//	d3d11SwapChain->Present(1, 0);
	//}

	//return 0;

	DPEngine* Engine = new DPEngine();

	if (!Engine->InitEngine(HInstance))
	{
		delete Engine;
		return 1;
	}

	Engine->Loop();

	delete Engine;
	
	return 0;
}