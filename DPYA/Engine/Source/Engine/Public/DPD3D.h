#pragma once

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#include "DPMath.h"

#include "DPMesh.h"

class DPD3D {
public:
	DPD3D(const DPD3D&) = delete;
	DPD3D& operator=(CONST DPD3D&) = delete;

	~DPD3D();

	// function prototypes
	bool Initialize(HWND HNWnd, const float InWidth, const float InHeight);    // sets up and initializes Direct3D

	void ClearView();
	bool PresentView();

	bool Draw(const Matrix4x4& ModelMatrix, const Matrix4x4& ViewMatrix, const DPArray<VertexData>& Vertices, const DPArray<unsigned int>& Indices, D3D11_PRIMITIVE_TOPOLOGY InTopology);

	static DPD3D* Get();

	inline ID3D11Device* GetDevice() { return Device; }
	inline ID3D11DeviceContext* GetDeviceContext() { return DeviceContext; }

private:
	DPD3D();

	static DPD3D* Instance;

	int ScreenWidth, ScreenHeight;

	ID3D11Device* Device;                   
	ID3D11DeviceContext* DeviceContext;           
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;
	ID3D11InputLayout* InputLayout;
	
	ID3D11Buffer* ConstantBuffer;
	ID3D11ShaderResourceView* TextureView;
	ID3D11Texture2D* Texture;

	IDXGISwapChain* SwapChain;

	DirectX::XMFLOAT4X4 ProjectionTM;
};