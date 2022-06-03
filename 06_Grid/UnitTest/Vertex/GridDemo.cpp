#include "stdafx.h"
#include "GridDemo.h"

//객체 초기화 및 생성
void GridDemo::Initialize()
{
	//셰이더 생성
	shader = new Shader(L"06_Grid.fx");

	//Create VertexBuffer
	{
		vertexCount = (width + 1) * (height + 1);
		vertices = new Vertex[vertexCount];

		for (UINT z = 0; z <= height; z++)
		{
			for (UINT x = 0; x <= width; ++x)
			{
				UINT index = (width + 1) * z + x;

				vertices[index].Position.x = (float)x - 15.f;
				vertices[index].Position.y = 0.0f - 0.5f;
				vertices[index].Position.z = (float)z - 15.f;
			}
		}
		//버퍼의 설명 정의
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		//정점 6개만큼의 크기이다.
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
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
		indexCount = width * height * 6;
		indices = new UINT[indexCount];

		UINT index = 0;
		for (UINT z = 0; z < height; ++z)
		{
			for (UINT x = 0; x < width; ++x)
			{
				indices[index] = (width + 1) * z + x;
				indices[index + 1] = (width + 1) * (z + 1) + x;
				indices[index + 2] = (width + 1) * z + x + 1;

				indices[index + 3] = indices[index + 2];
				indices[index + 4] = indices[index + 1];
				indices[index + 5] = (width + 1) * (z + 1) + x + 1;
				index += 6;
			}
		}

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT) * indexCount;
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subdata = { 0 };
		subdata.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &subdata, &indexBuffer));
	}
}

//소멸자
void GridDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

//매 프레임마다 데이터 업데이트
void GridDemo::Update()
{
	D3DXMatrixIdentity(&world);
}

//실제로 그릴 코드들
void GridDemo::Render()
{
	//정점정보 하나의 크기가 얼만큼 되는지
	UINT stride = sizeof(Vertex);
	//데이터끼리의 간격
	UINT offset = 0;

	//IA단계에 각 버퍼 세팅
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT,  offset);
	//IA단계에 정점을 어떤식으로 그릴건가 세팅
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
	shader->AsMatrix("World")->SetMatrix(world);

	Color color = Color(0, 0.5, 0.5, 1);
	shader->AsVector("Color")->SetFloatVector(color);

	//D3D::GetDC()->Draw(vertexCount, startVertexLocation) 과 같다.
	//pixel shader에서 0번 technique와 0번 pass를 사용하여 정점 6개를 그린다는 뜻
	shader->DrawIndexed(0, 0, indexCount);
}
