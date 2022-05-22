#include "stdafx.h"
#include "GridDemo.h"

//��ü �ʱ�ȭ �� ����
void GridDemo::Initialize()
{
	//���̴� ����
	shader = new Shader(L"06_Triangle.fx");

	//Create VertexBuffer
	{
		vertices[0].Position = Vector3(-0.5f, 0.0f, 0.0f);
		vertices[1].Position = Vector3(0.0f, 0.5f, 0.0f);
		vertices[2].Position = Vector3(0.5f, 0.0f, 0.0f);

		//������ ���� ����
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		//���� 6����ŭ�� ũ���̴�.
		desc.ByteWidth = sizeof(Vertex) * 6;
		//�� ���۸� ������������ Vertex Buffer�� �����Ұ��̴�.
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		//���ۿ� �� ���빰 ����
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		//���ؽ� ������ �ʱ�ȭ�� ������ �ѹ��� �̷����
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}


}

//�Ҹ���
void GridDemo::Destroy()
{
	SafeDelete(shader);
	SafeRelease(vertexBuffer);
	//SafeRelease(vertexBuffer2);
}

//�� �����Ӹ��� ������ ������Ʈ
void GridDemo::Update()
{
}

//������ �׸� �ڵ��
void GridDemo::Render()
{
	//�������� �ϳ��� ũ�Ⱑ ��ŭ �Ǵ���
	UINT stride = sizeof(Vertex);
	//�����ͳ����� ����
	UINT offset = 0;

	//IA�ܰ迡 VertexBuffer ����
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//IA�ܰ迡 ������ ������� �׸��ǰ� ����
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//D3D::GetDC()->Draw(vertexCount, startVertexLocation) �� ����.
	//pixel shader���� 0�� technique�� 0�� pass�� ����Ͽ� ���� 6���� �׸��ٴ� ��
	shader->Draw(0, 0, 6);

}
