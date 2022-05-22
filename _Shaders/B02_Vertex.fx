//�ĺ��� ��ġ�ؾ� ���� 
matrix World;
matrix View;
matrix Projection;

struct VertexInput
{
	float4 Position : Position;
};

struct VertexOutput
{
	float4 Position : SV_Position; //SV_Position�� �����ش޶�¶�?
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
	
	return output;
}

float4 PS(VertexOutput input) : SV_target
{
	return float4(1, 0, 0, 1);
}

float4 PS2(VertexOutput input) : SV_target
{
    return float4(0, 1, 0, 1);
}

//�����Ͷ����� ���� �ȼ��� ��� ä����ΰ�? 
RasterizerState FillMode_Wireframe
{
    FillMode = Wireframe;
};
    

technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));

        //SetRasterizerState(FillMode_Wireframe);
    }

    pass P1
    {
        SetRasterizerState(FillMode_Wireframe);

        SetVertexShader(CompileShader(vs_5_0, VS()));
        SetPixelShader(CompileShader(ps_5_0, PS()));
    }
}