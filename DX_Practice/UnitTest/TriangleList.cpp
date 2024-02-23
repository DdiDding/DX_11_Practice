#include "stdafx.h"
#include "TriangleList.h"

//객체 초기화 및 생성
void TriangleList::Initialize()
{
	//셰이더 생성
	shader = new Shader(L"06_Triangle.fx");

	//Create VertexBuffer
	{
		vertices[0].Position = Vector3(0.0f, 0.0f, 0.0f);
		vertices[1].Position = Vector3(0.0f, 1.0f, 0.0f);
		vertices[2].Position = Vector3(1.0f, 0.0f, 0.0f);

		//버퍼의 설명 정의
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		//정점 6개만큼의 크기이다.
		desc.ByteWidth = sizeof(Vertex) * 6;
		//이 버퍼를 파이프라인의 Vertex Buffer로 연결할것이다.
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//버퍼에 들어갈 내용물 정의
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		//버텍스 버퍼의 초기화와 생성이 한번에 이루어짐
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}
}

//소멸자
void TriangleList::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	//SafeRelease(vertexBuffer2);
}

//매 프레임마다 데이터 업데이트
void TriangleList::Update()
{
}

//실제로 그릴 코드들
void TriangleList::Render()
{
	//정점정보 하나의 크기가 얼만큼 되는지
	UINT stride = sizeof(Vertex);
	//데이터끼리의 간격
	UINT offset = 0;

	//IA단계에 VertexBuffer 세팅
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//IA단계에 정점을 어떤식으로 그릴건가 세팅
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//D3D::GetDC()->Draw(vertexCount, startVertexLocation) 과 같다.
	//pixel shader에서 0번 technique와 0번 pass를 사용하여 정점 6개를 그린다는 뜻
	shader->Draw(0, 0, 6);

}

/*D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer2, &stride, &offset);
D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

shader->Draw(0, 1, 6);*/

//VertexBuffer2
//{
//	vertices2[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
//	vertices2[1].Position = Vector3(0.0f, 0.0f, 0.0f);
//	vertices2[2].Position = Vector3(0.5f, -0.5f, 0.0f);

//	D3D11_BUFFER_DESC desc;
//	//구조체 초기화시 멤버안에 포인터변수가 존재할때 ZeroMemory로 초기화
//	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
//	desc.ByteWidth = sizeof(Vertex) * 6;
//	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

//	//GPU를 복사하기위해 사용? 뒤에 자세히나온다고함
//	D3D11_SUBRESOURCE_DATA subResource = { 0 };
//	subResource.pSysMem = vertices2;

//	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer2));
//}