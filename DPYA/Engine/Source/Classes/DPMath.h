#pragma once

#include <math.h>

namespace MathConstant
{
	static constexpr float MC_Epsilon = 1e-06f;
	static constexpr float MC_Pi = 3.1415926535897943484f;
}

struct Vector2
{
	float X, Y;

	Vector2()
		: X(0.0f)
		, Y(0.0f)
	{}

	Vector2(const float InX, const float InY)
		: X(InX)
		, Y(InY)
	{}

	Vector2(const Vector2& InVec)
	{
		X = InVec.X;
		Y = InVec.Y;
	}

	Vector2& operator=(const Vector2& InVec)
	{
		X = InVec.X;
		Y = InVec.Y;

		return *this;
	}

	inline Vector2 operator+(const Vector2& InVec) const
	{
		return Vector2(X + InVec.X, Y + InVec.Y);
	}
	inline Vector2 operator-(const Vector2& InVec) const
	{
		return Vector2(X - InVec.X, Y - InVec.Y);
	}

	Vector2& operator-()
	{
		X = -X;
		Y = -Y;

		return *this;
	}
	Vector2& operator+=(const Vector2& InVec)
	{
		X += InVec.X;
		Y += InVec.Y;

		return *this;
	}
	Vector2& operator-=(const Vector2& InVec)
	{
		X -= InVec.X;
		Y -= InVec.Y;

		return *this;
	}
	inline bool operator==(const Vector2& InVec) const
	{
		return (fabsf(X - InVec.X) <= MathConstant::MC_Epsilon) && (fabsf(Y - InVec.Y) <= MathConstant::MC_Epsilon);
	}
};

struct Vector3
{
	float X, Y, Z;

	Vector3()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
	{}

	Vector3(const float InX, const float InY, const float InZ)
		: X(InX)
		, Y(InY)
		, Z(InZ)
	{}

	Vector3(const Vector3& InVec)
	{
		X = InVec.X;
		Y = InVec.Y;
		Z = InVec.Z;
	}

	Vector3& operator=(const Vector3& InVec)
	{
		X = InVec.X;
		Y = InVec.Y;
		Z = InVec.Z;

		return *this;
	}

	inline Vector3 operator+(const Vector3& InVec) const
	{
		return Vector3(X+InVec.X, Y + InVec.Y, Z + InVec.Z);
	}
	inline Vector3 operator-(const Vector3& InVec) const
	{
		return Vector3(X - InVec.X, Y - InVec.Y, Z - InVec.Z);
	}

	Vector3& operator-()
	{
		X = -X;
		Y = -Y;
		Z = -Z;

		return *this;
	}
	Vector3& operator+=(const Vector3& InVec)
	{
		X += InVec.X;
		Y += InVec.Y;
		Z += InVec.Z;

		return *this;
	}
	Vector3& operator-=(const Vector3& InVec)
	{
		X -= InVec.X;
		Y -= InVec.Y;
		Z -= InVec.Z;

		return *this;
	}
	inline bool operator==(const Vector3& InVec) const
	{
		return (fabsf(X - InVec.X) <= MathConstant::MC_Epsilon) && (fabsf(Y - InVec.Y) <= MathConstant::MC_Epsilon) && (fabsf(Z - InVec.Z) <= MathConstant::MC_Epsilon);
	}
};

struct Vector4
{
	float X, Y, Z, W;

	Vector4()
		: X(0.0f)
		, Y(0.0f)
		, Z(0.0f)
		, W(0.0f)
	{}

	Vector4(const float InX, const float InY, const float InZ, const float InW)
		: X(InX)
		, Y(InY)
		, Z(InZ)
		, W(InW)
	{}

	Vector4(const Vector4& InVec)
	{
		X = InVec.X;
		Y = InVec.Y;
		Z = InVec.Z;
		W = InVec.W;
	}

	Vector4& operator=(const Vector4& InVec)
	{
		X = InVec.X;
		Y = InVec.Y;
		Z = InVec.Z;
		W = InVec.W;

		return *this;
	}

	inline Vector4 operator+(const Vector4& InVec) const 
	{
		return Vector4(X + InVec.X, Y + InVec.Y, Z + InVec.Z, W + InVec.W);
	}
	inline Vector4 operator-(const Vector4& InVec) const 
	{
		return Vector4(X - InVec.X, Y - InVec.Y, Z - InVec.Z, W - InVec.W);
	}

	Vector4& operator-()
	{
		X = -X; Y = -Y;
		Z = -Z; W = -W;

		return *this;
	}
	Vector4& operator+=(const Vector4& InVec)
	{
		X += InVec.X;
		Y += InVec.Y;
		Z += InVec.Z;
		W += InVec.W;

		return *this;
	}
	Vector4& operator-=(const Vector4& InVec)
	{
		X -= InVec.X;
		Y -= InVec.Y;
		Z -= InVec.Z;
		W -= InVec.W;

		return *this;
	}

	inline bool operator==(const Vector4& InVec) const
	{
		return (fabsf(X - InVec.X) <= MathConstant::MC_Epsilon) && (fabsf(Y - InVec.Y) <= MathConstant::MC_Epsilon) && (fabsf(Z - InVec.Z) <= MathConstant::MC_Epsilon) && (fabsf(W - InVec.W) <= MathConstant::MC_Epsilon);
	}
};

struct Matrix4x4
{
	union
	{
		struct
		{
			float M11, M12, M13, M14;
			float M21, M22, M23, M24;
			float M31, M32, M33, M34;
			float M41, M42, M43, M44;
		};
		float M[4][4];
	};

	Matrix4x4()
		: M11(0.f), M12(0.f), M13(0.f), M14(0.f)
		, M21(0.f), M22(0.f), M23(0.f), M24(0.f)
		, M31(0.f), M32(0.f), M33(0.f), M34(0.f)
		, M41(0.f), M42(0.f), M43(0.f), M44(0.f)
	{ }

	Matrix4x4(float _M11, float _M12, float _M13, float _M14, float _M21, float _M22, float _M23, float _M24, 
				float _M31, float _M32, float _M33, float _M34, float _M41, float _M42, float _M43, float _M44)
		: M11(_M11), M12(_M12), M13(_M13), M14(_M14)
		, M21(_M21), M22(_M22), M23(_M23), M24(_M24)
		, M31(_M31), M32(_M32), M33(_M33), M34(_M34)
		, M41(_M41), M42(_M42), M43(_M43), M44(_M44)
	{ }

	Matrix4x4(const Vector4& V1, const Vector4& V2, const Vector4& V3, const Vector4& V4)
		: M11(V1.X), M12(V1.Y), M13(V1.Z), M14(V1.W)
		, M21(V2.X), M22(V2.Y), M23(V2.Z), M24(V2.W)
		, M31(V3.X), M32(V3.Y), M33(V3.Z), M34(V3.W)
		, M41(V4.X), M42(V4.Y), M43(V4.Z), M44(V4.W)
	{ }

	static Matrix4x4 IdentityMatrix()
	{
		return Matrix4x4(1.f, 0.f, 0.f, 0.f, 
						0.f, 1.f, 0.f, 0.f, 
						0.f, 0.f, 1.f, 0.f, 
						0.f, 0.f, 0.f, 1.0f);
	}

	static Matrix4x4 TranslationMatrix(float InX, float InY, float InZ = 0.f)
	{
		return Matrix4x4(1.f, 0.f, 0.f, InX,
						0.f, 1.f, 0.f, InY,
						0.f, 0.f, 1.f, InZ,
						0.f, 0.f, 0.f, 1.0f);
	}

	static Matrix4x4 ScaleMatrix(float InX, float InY, float InZ = 0.f)
	{
		return Matrix4x4(InX, 0.f, 0.f, 0.f,
						0.f, InY, 0.f, 0.f,
						0.f, 0.f, InZ, 0.f,
						0.f, 0.f, 0.f, 1.0f);
	}

	inline void SetIdentity()
	{
		M11 = 1.f; M12 = 0.f; M13 = 0.f; M14 = 0.f;
		M21 = 0.f; M22 = 1.f; M23 = 0.f; M24 = 0.f;
		M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = 0.f;
		M41 = 0.f; M42 = 0.f; M43 = 0.f; M44 = 1.f;
	}
	inline void SetTranslation(float InX, float InY, float InZ = 0.f)
	{
		M11 = 1.f; M12 = 0.f; M13 = 0.f; M14 = InX;
		M21 = 0.f; M22 = 1.f; M23 = 0.f; M24 = InY;
		M31 = 0.f; M32 = 0.f; M33 = 1.f; M34 = InZ;
		M41 = 0.f; M42 = 0.f; M43 = 0.f; M44 = 1.f;
	}
	inline void SetScale(float InX, float InY, float InZ = 0.f)
	{
		M11 = InX; M12 = 0.f; M13 = 0.f; M14 = 0.f;
		M21 = 0.f; M22 = InY; M23 = 0.f; M24 = 0.f;
		M31 = 0.f; M32 = 0.f; M33 = InZ; M34 = 0.f;
		M41 = 0.f; M42 = 0.f; M43 = 0.f; M44 = 1.f;
	}

	float* ToFloats() const
	{
		float* Temp = new float[16];

		for (unsigned int i = 0; i < 4; i++)
		{
			for (unsigned int j = 0; j < 4; j++)
			{
				Temp[4 * i + j] = M[i][j];
			}
		}

		return Temp;
	}
};