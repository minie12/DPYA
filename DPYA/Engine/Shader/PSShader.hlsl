struct PS
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
};

float4 PSMain(PS Input) : SV_TARGET
{
	return Input.Color;
}