#include "stdafx.h"
#include "Cube.h"

//객체 초기화 및 생성
void Cube::Initialize()
{
	//셰이더 생성
	shader = new Shader(L"06_Grid.fx");

	//Transform Set
	r = Vector3(0, 0, 0);
	t = Vector3(0, 0, 0);


	//Create VertexBuffer
	{
		vertices[0].Position = Vector3(-0.5f, -0.5f, -0.5f);
		vertices[1].Position = Vector3(-0.5f, +0.5f, -0.5f);
		vertices[2].Position = Vector3(+0.5f, +0.5f, -0.5f);
		vertices[3].Position = Vector3(+0.5f, -0.5f, -0.5f);

		vertices[4].Position = Vector3(-0.5f, -0.5f, +0.5f);
		vertices[5].Position = Vector3(-0.5f, +0.5f, +0.5f);
		vertices[6].Position = Vector3(+0.5f, +0.5f, +0.5f);
		vertices[7].Position = Vector3(+0.5f, -0.5f, +0.5f);

		//버퍼의 설명 정의
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		//정점 6개만큼의 크기이다.
		desc.ByteWidth = sizeof(Vertex) * 8;
		//이 버퍼를 파이프라인의 Vertex Buffer로 연결할것이다.
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//버퍼에 들어갈 내용물 정의
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		//버텍스 버퍼의 초기화와 생성이 한번에 이루어짐
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//Create IndexBuffer
	{
		UINT indices[36] = {
			0, 1, 3, 3, 1, 2,
			1, 5, 2, 2, 5, 6,
			7, 6, 4, 4, 6, 5,
			3, 7, 4, 4, 0, 3,
			3, 2, 7, 7, 2, 6,
			4, 5, 0, 0, 5, 1
		};

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		desc.ByteWidth = sizeof(UINT) * 36;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}

	
}

//소멸자
void Cube::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

//매 프레임마다 데이터 업데이트
void Cube::Update()
{
	D3DXMatrixIdentity(&world);
	Translation(Context::Get()->GetLookPos());
	ImGui::SliderFloat3("Rotation", r, -180.f, 180.f);
	UpdateTransform();
}

//실제로 그릴 코드들
void Cube::Render()
{
	//정점정보 하나의 크기가 얼만큼 되는지
	UINT stride = sizeof(Vertex);
	//데이터끼리의 간격
	UINT offset = 0;

	//IA단계 세팅
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//IA단계에 정점을 어떤식으로 그릴건가 세팅
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
	shader->AsMatrix("World")->SetMatrix(world);

	Color color = Color(0, 1, 0, 1);
	shader->AsVector("Color")->SetFloatVector(color);

	shader->DrawIndexed(0, 0, 36);
}

void Cube::Rotation(const Vector3 & data)
{
	r = data;
}

void Cube::Translation(const Vector3 & data)
{
	t = data;
}

void Cube::UpdateTransform()
{

	Matrix X, Y, Z;
	D3DXMatrixRotationX(&X, r.x);
	D3DXMatrixRotationY(&Y, r.y);
	D3DXMatrixRotationZ(&Z, r.z);
	world = X * Y * Z;

	Matrix T;
	D3DXMatrixTranslation(&T, t.x, t.y, t.z);
	world *= T;
}
