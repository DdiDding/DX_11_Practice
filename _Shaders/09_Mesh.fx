matrix World, View, Projection;
float3 LightDirection = float3(-1, -1, 1);
float4 Color;

struct VertexInput
{
	float4 Position : Position;
	float3 Normal: Normal;
};

struct VertexOutput
{
	float4 Position : SV_Position;
    float3 Normal : Normal;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Normal = mul(input.Normal, (float3x3) World);
    //output.Color = float4(1, 0, 0, 1);
    
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
	
    
    return output;
}

float4 PS(VertexOutput input) : SV_target
{
    float NdotL = dot(-LightDirection, normalize(input.Normal));
    return Color * NdotL;
}

//레스터라이즈 계산된 픽셀을 어떻게 채울것인가 설정 값 ( 아직 설정한게 아님 )
RasterizerState FillMode_Wireframe
{
    FillMode = Wireframe;
};

technique11 T0
{
	pass P0
	{
        SetRasterizerState(FillMode_Wireframe);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}