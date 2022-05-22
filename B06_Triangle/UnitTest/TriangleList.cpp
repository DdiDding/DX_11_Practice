#include "stdafx.h"
#include "TriangleList.h"

//��ü �ʱ�ȭ �� ����
void TriangleList::Initialize()
{
	//���̴� ����
	shader = new Shader(L"B02_Vertex.fx");

	//Create VertexBuffer
	{
		vertices[0].Position = Vector3(-0.5f, -0.5f, 0.0f);
		vertices[1].Position = Vector3(-0.5f, +0.5f, 0.0f);
		vertices[2].Position = Vector3(+0.5f, -0.5f, 0.0f);
		vertices[3].Position = Vector3(+0.5f, +0.5f, 0.0f);

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

		D3DXMatrixIdentity(&world);
	}


	{
		indeces[0] = 0;
		indeces[1] = 1;
		indeces[2] = 2;

		indeces[3] = 2;
		indeces[4] = 1;
		indeces[5] = 3;

		//������ ���� ����
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

		//���� 6����ŭ�� ũ���̴�.
		desc.ByteWidth = sizeof(UINT) * 6;
		//�� ���۸� ������������ Vertex Buffer�� �����Ұ��̴�.
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		//���ۿ� �� ���빰 ����
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indeces;

		//���ؽ� ������ �ʱ�ȭ�� ������ �ѹ��� �̷����
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &indexBuffer));
	}

}

//�Ҹ���
void TriangleList::Destroy()
{
	//ID3D11Bufferó�� I�� �ٴ°� IUnknown�� ��ӹ��� COM��ü�̴�.
	//�� COM��ü�� Ư���Լ��� ������ �ϰ� �����Ҷ��� COM�� Release �޼��带 ȣ���� �����Ѵ�.
	//���� Ƚ���� 0�� �Ǹ� ���������� delete this;�� �����Ѵ�.
	//i�ڰ� ���� ������ new�� �����Ͽ� delete�� ����
	SafeDelete(shader);
	//i�� �����Ŵ� release�� ����
	SafeRelease(vertexBuffer);
	//SafeRelease(vertexBuffer2);
	SafeRelease(indexBuffer);
}

//�� �����Ӹ��� ������ ������Ʈ
void TriangleList::Update()
{
	D3DXMATRIX a = Context::Get()->View();
	D3DXMATRIX b = Context::Get()->Projection();
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());


}

//������ �׸� �ڵ��
void TriangleList::Render()
{
	//�������� �ϳ��� ũ�Ⱑ ��ŭ �Ǵ���
	UINT stride = sizeof(Vertex);
	//�����ͳ����� ����
	UINT offset = 0;

	//IA�ܰ迡 VertexBuffer ����
	//2��° �Ű������� ��� ������ �ϴ°� �ִµ� ���߿� �ν��Ͻ̶� �̿�
	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//IA�ܰ迡 ������ ������� �׸��ǰ� ����
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//ImGui::InputInt()

	static Vector3 position = Vector3(0, 0, 0);
	ImGui::SliderFloat2("Position", position, -10, 10);

	world._41 = position.x;
	world._42 = position.y;

	shader->AsMatrix("World")->SetMatrix(world);

	//D3D::GetDC()->Draw(vertexCount, startVertexLocation) �� ����.
	//startVertexLocation : ���°�������� �׸��°�?
	//pixel shader���� 0�� technique�� 0�� pass�� ����Ͽ� ���� 6���� �׸��ٴ� ��
	shader->DrawIndexed(0, 0, 6);
}