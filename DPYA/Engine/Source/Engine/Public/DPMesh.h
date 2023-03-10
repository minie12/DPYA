#pragma once

#include "DPCore.h"
#include "DPMath.h"
#include "DPArray.h"

enum MeshShape
{
	MS_Triangle = 0,
	MS_Rectangle,
	MS_Ellipse,
};

struct VertexData
{
	Vector3 Position;
	Vector4 Color;
	Vector2 UV;

	VertexData()
		: Position(0.0f, 0.0f, 0.0f)
		, Color(1.0f, 0.0f, 0.0f, 1.0f)
		, UV(0.0f, 0.0f)
	{}

	VertexData(const Vector3& InPosition, const Vector4& InColor, const Vector2& InUV)
		: Position(InPosition)
		, Color(InColor)
		, UV(InUV)
	{}

	VertexData& operator=(const VertexData& InData)
	{
		Position = InData.Position;
		Color = InData.Color;
		UV = InData.UV;

		return *this;
	}
};

class DPMesh
{
public:
	DPMesh();
	virtual ~DPMesh() { }
	DPMesh(const DPMesh& InMesh);

	virtual void CreateAtCenter(float InWidth, float InHeight, const Vector4& InColor, float InX = 0.0f, float InY = 0.0f) = 0;
	virtual void CreateAtTopLeft(float InWidth, float InHeight, const Vector4& InColor, float InX = 0.0f, float InY = 0.0f) = 0;
	virtual MeshShape GetShape() = 0;

	inline const DPArray<VertexData>& GetVertices() const { return DrawVertices; }
	inline const DPArray<unsigned int>& GetIndices() const { return DrawIndices; }
	inline unsigned int GetVertexCount() const { return DrawVertices.Num(); }
	inline unsigned int GetIndexCount() const { return DrawIndices.Num(); }
	inline const Vector3& GetPosition() const { return Position; }
	inline void SetPosition(const Vector3& InPosition) { Position = InPosition; }
	inline float GetWidth() const { return Width; }
	inline float GetHeight() const { return Height; }
	inline void SetSize(const float InW, const float InH) { Width = fabsf(InW); Height = fabsf(InH); }


protected:
	DPArray<VertexData> DrawVertices;
	DPArray<unsigned int> DrawIndices;

	Vector3 Position;
	float Width;
	float Height;
};

class DPTriangleMesh : public DPMesh
{
public:
	DPTriangleMesh() {}
	~DPTriangleMesh() {}
	DPTriangleMesh& operator=(const DPTriangleMesh& InMesh);

	void CreateAtCenter(float InWidth, float InHeight, const Vector4& InColor, float InX = 0.0f, float InY = 0.0f) override;
	void CreateAtTopLeft(float InWidth, float InHeight, const Vector4& InColor, float InX = 0.0f, float InY = 0.0f) override;
	MeshShape GetShape() override { return MeshShape::MS_Rectangle; }
};

class DPRectangleMesh : public DPMesh
{
public:
	DPRectangleMesh() {}
	~DPRectangleMesh() {}
	DPRectangleMesh& operator=(const DPRectangleMesh& InMesh);

	void CreateAtCenter(float InWidth, float InHeight, const Vector4& InColor, float InX = 0.0f, float InY = 0.0f) override;
	void CreateAtTopLeft(float InWidth, float InHeight, const Vector4& InColor, float InX = 0.0f, float InY = 0.0f) override;
	MeshShape GetShape() override { return MeshShape::MS_Triangle; }
};

class DPEllipseMesh : public DPMesh
{
public:
	DPEllipseMesh() {}
	~DPEllipseMesh() {}
	DPEllipseMesh& operator=(const DPEllipseMesh& InMesh);

	void CreateAtCenter(float InWidth, float InHeight, const Vector4& InColor, float InX = 0.0f, float InY = 0.0f) override;
	void CreateAtTopLeft(float InWidth, float InHeight, const Vector4& InColor, float InX = 0.0f, float InY = 0.0f) override;
	MeshShape GetShape() override { return MeshShape::MS_Ellipse; }
};