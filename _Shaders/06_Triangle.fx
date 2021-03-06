struct VertexInput
{
	float4 Position : Position;
};

struct VertexOutput
{
	float4 Position : SV_Position;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.Position = input.Position;
	
	return output;
}

float4 PS_R(VertexOutput input) : SV_target
{
	return float4(1, 0, 0, 1);
}

float4 PS_G(VertexOutput input) : SV_target
{
    return float4(0, 1, 0, 1);
}

float4 PS_B(VertexOutput input) : SV_target
{
    return float4(0, 0, 1, 1);
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
		SetPixelShader(CompileShader(ps_5_0, PS_R()));
	}


    pass P1
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_G()));
    }

    pass P2
    {
        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS_B()));
    }
}