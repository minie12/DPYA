#include "DPActor.h"

DPActor::DPActor()
	: Position(0.f, 0.f, 0.f)
	, Width(0.f), Height(0.f)
	, TM(Matrix4x4::IdentityMatrix())
	, Mesh(nullptr)
{ }

DPActor::~DPActor()
{
	SafeDelete(Mesh);
}

DPActor::DPActor(const DPActor& InActor)
{
	switch (InActor.GetShape())
	{
	case MeshShape::MS_Rectangle:
		Mesh = new DPRectangleMesh();
		break;
	case MeshShape::MS_Triangle:
		Mesh = new DPTriangleMesh();
		break;
	case MeshShape::MS_Ellipse:
		Mesh = new DPEllipseMesh();
		break;
	}
	*Mesh = InActor.GetMesh();
	Position = InActor.GetPosition();
	Width = InActor.GetWidth();
	Height = InActor.GetHeight();
	TM = InActor.GetTM();
}
DPActor& DPActor::operator=(const DPActor& InActor)
{
	switch (InActor.GetShape())
	{
	case MeshShape::MS_Rectangle:
		Mesh = new DPRectangleMesh();
		break;
	case MeshShape::MS_Triangle:
		Mesh = new DPTriangleMesh();
		break;
	case MeshShape::MS_Ellipse:
		Mesh = new DPEllipseMesh();
		break;
	}
	*(Mesh) = InActor.GetMesh();
	Position = InActor.GetPosition();
	Width = InActor.GetWidth();
	Height = InActor.GetHeight();
	TM = InActor.GetTM();
	return *this;
}

void DPActor::CreateMesh(MeshShape InShape, const float InWidth, const float InHeight, const Vector3& InPosition, const Vector4& InColor)
{
	Position = InPosition;
	Width = InWidth; Height = InHeight;
	TM.SetTranslation(InPosition.X, InPosition.Y);

	switch (InShape)
	{
	case MS_Triangle:
		Mesh = new DPTriangleMesh();
		Mesh->CreateAtCenter(InWidth, InHeight, InColor);
		break;
	case MS_Rectangle:
		Mesh = new DPRectangleMesh();
		Mesh->CreateAtCenter(InWidth, InHeight, InColor);
		break;
	case MS_Ellipse:
		Mesh = new DPEllipseMesh();
		Mesh->CreateAtCenter(InWidth, InHeight, InColor);
		break;
	default:
		// No such mesh found.
		break;
	}
}

