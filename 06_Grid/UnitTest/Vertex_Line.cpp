#include "stdafx.h"
#include "Vertex_Line.h"

//��ü �ʱ�ȭ �� ����
void Vertex_Line::Initialize()
{
	shader = new Shader(L"01_Vertex.fx");

	vertices[0].Position = Vector3(0.0f, 0.0f, 0.0f);
	vertices[1].Position = Vector3(1.0f, 0.0f, 0.0f);

	D3D11_BUFFER_DESC desc;
	//����ü �ʱ�ȭ�� ����ȿ� �����ͺ����� �����Ҷ� ZeroMemory�� �ʱ�ȭ
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(Vertex) * 2;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
}

//�Ҹ���
void Vertex_Line::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
}

//�� �����Ӹ��� ������ ������Ʈ
void Vertex_Line::Update()
{
}

//������ �׸� �ڵ��
void Vertex_Line::Render()
{
	//�������� �ϳ��� ũ�Ⱑ ��ŭ �Ǵ���
	UINT stride = sizeof(Vertex);
	//�����ͳ����� ����
	UINT offset = 0;

	//IA�ܰ迡 VertexBuffer ����
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//IA�ܰ迡 ������ ������� �׸��ǰ� ����
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//D3D::GetDC()->Draw(vertexCount, startVertexLocation) �� ����.
	shader->Draw(0, 1, 2);
}

