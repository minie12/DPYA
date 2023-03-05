#include "DPEngine.h"

#include "DPD3D.h"
#include "DPTimer.h"
#include "DPGameEngine.h"

static const unsigned int ScreenWidth = 600;
static const unsigned int ScreenHeight = 800;

bool DPEngine::InitEngine(HINSTANCE HInstance)
{
	Windows = DPWindows::Get();

	if (!Windows->InitWindows(HInstance))
		return false;

	D3D = DPD3D::Get();

	if (!D3D->Initialize(Windows->GetHWNND(), ScreenWidth, ScreenHeight))
		return false;

	Timer = new DPTimer();        

	GameEngine = new DPGameEngine();
	
	return true;
}

void DPEngine::Loop()
{
	while (true)
	{
		if (!Windows->Tick())
			break;

		float DeltaTime = Timer->GetDeltaTime();
		
		GameEngine->Tick(DeltaTime);
		
		DrawTick();
	}

	// End Engine
	// delete D3D;
	// delete Windows;
}

void DPEngine::DrawTick()
{
	D3D->ClearView();

	/*if (!D3D->Draw(Matrix4x4::IdentityMatrix(), Matrix4x4::IdentityMatrix(), Mesh->GetVertices(), Mesh->GetIndices(), D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST))
		return;*/

	GameEngine->Draw(D3D);
	// UIManager Draw
	
	// D3D: Present View
	D3D->PresentView();
}

