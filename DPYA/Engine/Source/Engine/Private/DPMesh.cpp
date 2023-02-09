#include "DPMesh.h"

DPMesh::DPMesh()
	: Position(0.0f, 0.0f, 0.0f)
	, Width(0.0f)
	, Height(0.0f)
{ }

void DPTriangleMesh::CreateAtCenter(float InWidth, float InHeight, const Vector4& InColor, float InX, float InY)
{
	SetSize(InWidth, InHeight);

	float HalfWidth = Width * 0.5f;
	float HalfHeight = Height * 0.5f;

	DrawVertices.Add(VertexData(Vector3(InX            , InY + HalfHeight, 0.0f), InColor, Vector2(0.5f, 0.0f)));
	DrawVertices.Add(VertexData(Vector3(InX + HalfWidth, InY - HalfHeight, 0.0f), InColor, Vector2(1.0f, 1.0f)));
	DrawVertices.Add(VertexData(Vector3(InX - HalfWidth, InY - HalfHeight, 0.0f), InColor, Vector2(0.0f, 1.0f)));

	DrawIndices.Add(0);
	DrawIndices.Add(1);
	DrawIndices.Add(2);
}

void DPTriangleMesh::CreateAtTopLeft(float InWidth, float InHeight, const Vector4 & InColor, float InX, float InY)
{
	SetSize(InWidth, InHeight);

	float HalfWidth = Width * 0.5f;

	DrawVertices.Add(VertexData(Vector3(InX + HalfWidth, InY         , 0.0f), InColor, Vector2(0.5f, 0.0f)));
	DrawVertices.Add(VertexData(Vector3(InX +     Width, InY - Height, 0.0f), InColor, Vector2(1.0f, 1.0f)));
	DrawVertices.Add(VertexData(Vector3(InX            , InY - Height, 0.0f), InColor, Vector2(0.0f, 1.0f)));

	DrawIndices.Add(0);
	DrawIndices.Add(1);
	DrawIndices.Add(2);
}

void DPRectangleMesh::CreateAtCenter(float InWidth, float InHeight, const Vector4& InColor, float InX, float InY)
{
	SetSize(InWidth, InHeight);

	float HalfWidth = Width * 0.5f;
	float HalfHeight = Height * 0.5f;

	DrawVertices.Add(VertexData(Vector3(InX - HalfWidth, InY + HalfHeight, 0.0f), InColor, Vector2(0.0f, 0.0f)));
	DrawVertices.Add(VertexData(Vector3(InX + HalfWidth, InY + HalfHeight, 0.0f), InColor, Vector2(1.0f, 0.0f)));
	DrawVertices.Add(VertexData(Vector3(InX + HalfWidth, InY - HalfHeight, 0.0f), InColor, Vector2(1.0f, 1.0f)));
	DrawVertices.Add(VertexData(Vector3(InX - HalfWidth, InY - HalfHeight, 0.0f), InColor, Vector2(0.0f, 1.0f)));

	DrawIndices.Add(0);
	DrawIndices.Add(1);
	DrawIndices.Add(2);
	DrawIndices.Add(0);
	DrawIndices.Add(2);
	DrawIndices.Add(3);
}

void DPRectangleMesh::CreateAtTopLeft(float InWidth, float InHeight, const Vector4 & InColor, float InX, float InY)
{
	SetSize(InWidth, InHeight);

	DrawVertices.Add(VertexData(Vector3(InX        , InY         , 0.0f), InColor, Vector2(0.0f, 0.0f)));
	DrawVertices.Add(VertexData(Vector3(InX + Width, InY         , 0.0f), InColor, Vector2(1.0f, 0.0f)));
	DrawVertices.Add(VertexData(Vector3(InX + Width, InY - Height, 0.0f), InColor, Vector2(1.0f, 1.0f)));
	DrawVertices.Add(VertexData(Vector3(InX        , InY - Height, 0.0f), InColor, Vector2(0.0f, 1.0f)));

	DrawIndices.Add(0);
	DrawIndices.Add(1);
	DrawIndices.Add(2);
	DrawIndices.Add(0);
	DrawIndices.Add(2);
	DrawIndices.Add(3);
}

void DPCircleMesh::CreateAtCenter(float InWidth, float InHeight, const Vector4& InColor, float InX, float InY)
{
	SetSize(InWidth, InHeight);

	float HalfWidth = Width * 0.5f;
	float HalfHeight = Height * 0.5f;

	unsigned int VertexCount = 50;
	
	float RadianPerCount = 2 * MathConstant::MC_Pi / 50;
	for (unsigned int Index = 0; Index < VertexCount; Index++)
	{
		float Radian = RadianPerCount * Index;
		DrawVertices.Add(VertexData(Vector3( InX + cosf(Radian) * HalfWidth, InY + sinf(Radian) * HalfHeight, 0.0f), InColor, Vector2(0.5f*(cosf(Radian)+1), 0.5f*(sinf(Radian)+1))));
	}

	for (unsigned int Index = 1; Index < VertexCount-1; Index++)
	{
		DrawIndices.Add(0);
		DrawIndices.Add(Index);
		DrawIndices.Add(Index+1);
	}
}

void DPCircleMesh::CreateAtTopLeft(float InWidth, float InHeight, const Vector4 & InColor, float InX, float InY)
{
	SetSize(InWidth, InHeight);

	float HalfWidth = Width * 0.5f;
	float HalfHeight = Height * 0.5f;

	float CenterX = InX + HalfWidth;
	float CenterY = InY - HalfHeight;

	unsigned int VertexCount = 50;

	float RadianPerCount = 2 * MathConstant::MC_Pi / 50;
	for (unsigned int Index = 0; Index < VertexCount; Index++)
	{
		float Radian = RadianPerCount * Index;
		DrawVertices.Add(VertexData(Vector3(CenterX + cosf(Radian) * HalfWidth, CenterY + sinf(Radian) * HalfHeight, 0.0f), InColor, Vector2(0.5f*(cosf(Radian) + 1), 0.5f*(sinf(Radian) + 1))));
	}

	for (unsigned int Index = 1; Index < VertexCount - 1; Index++)
	{
		DrawIndices.Add(0);
		DrawIndices.Add(Index);
		DrawIndices.Add(Index + 1);
	}
}
