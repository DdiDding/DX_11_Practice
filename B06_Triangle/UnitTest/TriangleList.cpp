#include "stdafx.h"
#include "TriangleList.h"

//객체 초기화 및 생성
void TriangleList::Initialize()
{
	//셰이더 생성
	shader = new Shader(L"B02_Vertex.fx");

	//Create VertexBuffer
	{
		vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
		vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
		vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

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

		D3DXMatrixIdentity(&world);
	}


	{
		indeces[0] = 0;
		indeces[1] = 1;
		indeces[2] = 2;

		indeces[3] = 2;
		indeces[4] = 1;
		indeces[5] = 3;

		//버퍼의 설명 정의
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		//정점 6개만큼의 크기이다.
		desc.ByteWidth = sizeof(UINT) * 6;
		//이 버퍼를 파이프라인의 Vertex Buffer로 연결할것이다.
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		//버퍼에 들어갈 내용물 정의
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indeces;

		//버텍스 버퍼의 초기화와 생성이 한번에 이루어짐
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}

}

//소멸자
void TriangleList::Destroy()
{
	//ID3D11Buffer처럼 I가 붙는건 IUnknown을 상속받은 COM객체이다.
	//이 COM객체는 특정함수로 생성을 하고 삭제할때도 COM의 Release 메서드를 호출해 삭제한다.
	//참조 횟수가 0이 되면 내부적으로 delete this;를 수행한다.
	//i자가 붙지 않은건 new로 생성하여 delete로 해제
	SafeDelete(shader);
	//i가 붙은거는 release로 해제
	SafeRelease(vertexBuffer);
	//SafeRelease(vertexBuffer2);
	SafeRelease(indexBuffer);
}

//매 프레임마다 데이터 업데이트
void TriangleList::Update()
{
	D3DXMATRIX a = Context::Get()->View();
	D3DXMATRIX b = Context::Get()->Projection();
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());


}

//실제로 그릴 코드들
void TriangleList::Render()
{
	//정점정보 하나의 크기가 얼만큼 되는지
	UINT stride = sizeof(Vertex);
	//데이터끼리의 간격
	UINT offset = 0;

	//IA단계에 VertexBuffer 세팅
	//2번째 매개변수에 몇개가 들어갈건지 하는게 있는데 나중에 인스턴싱때 이용
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//IA단계에 정점을 어떤식으로 그릴건가 세팅
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//ImGui::InputInt()

	static Vector3 position = Vector3(0, 0, 0);
	ImGui::SliderFloat2("Position", position, -10, 10);

	world._41 = position.x;
	world._42 = position.y;

	shader->AsMatrix("World")->SetMatrix(world);

	//D3D::GetDC()->Draw(vertexCount, startVertexLocation) 과 같다.
	//startVertexLocation : 몇번째정점부터 그리는가?
	//pixel shader에서 0번 technique와 0번 pass를 사용하여 정점 6개를 그린다는 뜻
	shader->DrawIndexed(0, 0, 6);
}