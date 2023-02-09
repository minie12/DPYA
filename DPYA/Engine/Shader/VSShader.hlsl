cbuffer ConstantBuffer : register(b0)
{
	float4x4 ModelMatrix;
	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
}

struct VS
{
	float3 Position : POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};

struct PS
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};

PS VSMain(VS Input)
{
	PS Output;
	Output.Position = float4(Input.Position, 1.0f);
	Output.Color = Input.Color;
	Output.UV = float2(0.0f, 0.0f);

	return Output;
}