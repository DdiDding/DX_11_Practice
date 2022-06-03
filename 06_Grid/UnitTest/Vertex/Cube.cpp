#include "stdafx.h"
#include "Cube.h"

//��ü �ʱ�ȭ �� ����
void Cube::Initialize()
{
	//���̴� ����
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

		//������ ���� ����
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		//���� 6����ŭ�� ũ���̴�.
		desc.ByteWidth = sizeof(Vertex) * 8;
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

//�Ҹ���
void Cube::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

//�� �����Ӹ��� ������ ������Ʈ
void Cube::Update()
{
	D3DXMatrixIdentity(&world);
	Translation(Context::Get()->GetLookPos());
	ImGui::SliderFloat3("Rotation", r, -180.f, 180.f);
	UpdateTransform();
}

//������ �׸� �ڵ��
void Cube::Render()
{
	//�������� �ϳ��� ũ�Ⱑ ��ŭ �Ǵ���
	UINT stride = sizeof(Vertex);
	//�����ͳ����� ����
	UINT offset = 0;

	//IA�ܰ� ����
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, offset);
	//IA�ܰ迡 ������ ������� �׸��ǰ� ����
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
