#include "stdafx.h"
#include "Vertex_Line2.h"

//객체 초기화 및 생성
void Vertex_Line2::Initialize()
{
	shader = new Shader(L"04_Vertex.fx");

	vertices[0].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[1].Position = Vector3(1.0f, 0.0f, 0.0f);

	vertices[2].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[3].Position = Vector3(0.5f, 0.0f, 0.0f);

	D3D11_BUFFER_DESC desc;
	//구조체 초기화시 멤버안에 포인터변수가 존재할때 ZeroMemory로 초기화
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 2;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
}

//소멸자
void Vertex_Line2::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

//매 프레임마다 데이터 업데이트
void Vertex_Line2::Update()
{
}

//실제로 그릴 코드들
void Vertex_Line2::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;


	//DC가 device context
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	shader->Draw(0, 1, 2);
}
