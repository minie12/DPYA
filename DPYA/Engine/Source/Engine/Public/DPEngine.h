#pragma once

#include "DPCore.h"
#include "DPSmartPointer.h"

#include "DPWindows.h"
class DPD3D;
class DPTimer;
class DPCircleMesh;

class DPEngine
{
public:
	DPEngine() { }
	~DPEngine() { }

	bool InitEngine(HINSTANCE HInstance);
	void Loop();
	void DrawTick();

private:
	DPD3D* D3D;
	DPWindows* Windows;
	DPTimer* Timer;

	DPCircleMesh* Mesh;
};