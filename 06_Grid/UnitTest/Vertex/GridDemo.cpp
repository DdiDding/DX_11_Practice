#include "stdafx.h"
#include "GridDemo.h"

//��ü �ʱ�ȭ �� ����
void GridDemo::Initialize()
{
	//���̴� ����
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
		//������ ���� ����
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		//���� 6����ŭ�� ũ���̴�.
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
		//�� ���۸� ������������ Vertex Buffer�� �����Ұ��̴�.
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//���ۿ� �� ���빰 ����
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		//���ؽ� ������ �ʱ�ȭ�� ������ �ѹ��� �̷����
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

//�Ҹ���
void GridDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

//�� �����Ӹ��� ������ ������Ʈ
void GridDemo::Update()
{
	D3DXMatrixIdentity(&world);
}

//������ �׸� �ڵ��
void GridDemo::Render()
{
	//�������� �ϳ��� ũ�Ⱑ ��ŭ �Ǵ���
	UINT stride = sizeof(Vertex);
	//�����ͳ����� ����
	UINT offset = 0;

	//IA�ܰ迡 �� ���� ����
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT,  offset);
	//IA�ܰ迡 ������ ������� �׸��ǰ� ����
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
	shader->AsMatrix("World")->SetMatrix(world);

	Color color = Color(0, 0.5, 0.5, 1);
	shader->AsVector("Color")->SetFloatVector(color);

	//D3D::GetDC()->Draw(vertexCount, startVertexLocation) �� ����.
	//pixel shader���� 0�� technique�� 0�� pass�� ����Ͽ� ���� 6���� �׸��ٴ� ��
	shader->DrawIndexed(0, 0, indexCount);
}
