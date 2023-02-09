#pragma once

#include "DPMath.h"
#include "DPSmartPointer.h";

class DPMesh;

class DPActor
{
public:

private:
	DPSharedPtr<DPMesh> Mesh;

	Vector3 Position;
	float Width, Height;

	Matrix4x4 TM;
};