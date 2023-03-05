#pragma once

#include "DPMath.h"
#include "DPSmartPointer.h"

#include "DPMesh.h"

enum MeshShape;

class DPActor
{
public:
	DPActor();
	~DPActor();
	DPActor(const DPActor& InActor);
	DPActor& operator=(const DPActor& InActor);

	void CreateMesh(MeshShape InShape, const float InWidth, const float InHeight, const Vector3& InPosition, const Vector4& InColor);

	inline const DPMesh& GetMesh() const { return *Mesh; }
	inline const Vector3& GetPosition() const { return Position; }
	inline float GetWidth() const { return Width; }
	inline float GetHeight() const { return Height; }
	inline const Matrix4x4& GetTM() const { return TM; }
	inline MeshShape GetShape() const { return Mesh->GetShape(); }

private:
	DPMesh* Mesh;

	Vector3 Position;
	float Width, Height;

	Matrix4x4 TM;
};