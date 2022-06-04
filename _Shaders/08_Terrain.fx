matrix World, View, Projection;
float3 LightDirection;

struct VertexInput
{
	float4 Position : Position;
	float3 Normal: Normal;
};

struct VertexOutput
{
	float4 Position : SV_Position;
    float4 Color : Color;
    float3 Normal : Normal;
};

float3 GetHeightColor(float y)
{
    float3 color = 1.0f;
    
    if (y > 20.f)
        color = float3(1, 0, 0);
    else if (y > 15.0f)
        color = float3(0, 1, 0);
    else if (y > 10.0f)
        color = float3(0, 0, 1);
    else if (y > 5.0f)
        color = float3(0, 0.5, 0.5);
    
    return color;
}

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Color = float4(GetHeightColor(output.Position.y), 1); //������?
    output.Normal = mul(input.Normal, (float3x3) World);
    
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
	
    
    return output;
}

float4 PS(VertexOutput input) : SV_target
{
    float NdotL = dot(-LightDirection, normalize(input.Normal));
    return input.Color * NdotL;
}

//�����Ͷ����� ���� �ȼ��� ��� ä����ΰ� ���� �� ( ���� �����Ѱ� �ƴ� )
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