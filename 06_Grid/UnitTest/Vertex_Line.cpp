#include "stdafx.h"
#include "Vertex_Line.h"

//객체 초기화 및 생성
void Vertex_Line::Initialize()
{
	shader = new Shader(L"01_Vertex.fx");

	vertices[0].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[1].Position = Vector3(1.0f, 0.0f, 0.0f);

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
void Vertex_Line::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

//매 프레임마다 데이터 업데이트
void Vertex_Line::Update()
{
}

//실제로 그릴 코드들
void Vertex_Line::Render()
{
	//정점정보 하나의 크기가 얼만큼 되는지
	UINT stride = sizeof(Vertex);
	//데이터끼리의 간격
	UINT offset = 0;

	//IA단계에 VertexBuffer 세팅
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//IA단계에 정점을 어떤식으로 그릴건가 세팅
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//D3D::GetDC()->Draw(vertexCount, startVertexLocation) 과 같다.
	shader->Draw(0, 1, 2);
}

