#include "Framework.h"
#include "Terrain.h"

Terrain::Terrain(Shader * shader, wstring heightFile)
	: shader(shader)
{
	heightMap = new Texture(heightFile);

	CreateVertexData();
	CreateIndexData();
	CreateNormalData();
	CreateBuffer();
}

Terrain::~Terrain()
{
	SafeDelete(heightMap);
	SafeDeleteArray(vertices);
	SafeDeleteArray(indices);

	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void Terrain::Update()
{
	Matrix world;
	D3DXMatrixIdentity(&world);

	shader->AsMatrix("World")->SetMatrix(world);
	shader->AsMatrix("View")->SetMatrix(Context::Get()->View());
	shader->AsMatrix("Projection")->SetMatrix(Context::Get()->Projection());
}

void Terrain::Render()
{
	UINT stride = sizeof(TerrainVertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	shader->DrawIndexed(0, 1, indexCount);
}

void Terrain::CreateVertexData()
{
	vector<Color> heights;
	//DXGI_FORMAT_R8G8B8A8_UNORM �� Rä�� 8��Ʈ(256���� ��) ��  0 ~ 1���� ����ȭ ���� �����
	heightMap->ReadPixel(DXGI_FORMAT_R8G8B8A8_UNORM, &heights);

	width = heightMap->GetWidth();
	height = heightMap->GetHeight();

	vertexCount = width * height;
	vertices = new TerrainVertex[vertexCount];
	for (UINT z = 0; z < height; ++z)
	{
		for (UINT x = 0; x < width; ++x)
		{
			UINT index = width * z + x;
			UINT heightIndex = (height - 1 - z) * width + x;

			vertices[index].Position.x = x;
			vertices[index].Position.y = heights[heightIndex].r * 255.f / 10.f;
			vertices[index].Position.z = z;
		}
	}
}

void Terrain::CreateIndexData()
{
	indexCount = (width - 1) * (height - 1) * 6;
	indices = new UINT[indexCount];

	UINT index = 0;
	for (UINT z = 0; z < height -1; ++z)
	{
		for (UINT x = 0; x < width -1; ++x)
		{
			indices[index + 0] = width * z + x;
			indices[index + 1] = width * (z + 1) + x;
			indices[index + 2] = width * z + x + 1;

			indices[index + 3] = indices[index + 2];
			indices[index + 4] = indices[index + 1];
			indices[index + 5] = width * (z + 1) + x + 1;
			index += 6;
		}
	}
}

void Terrain::CreateBuffer()
{
	//������ ���� ����
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	//���� 6����ŭ�� ũ���̴�.
	desc.ByteWidth = sizeof(TerrainVertex) * vertexCount;
	//�� ���۸� ������������ Vertex Buffer�� �����Ұ��̴�.
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//���ۿ� �� ���빰 ����
	D3D11_SUBRESOURCE_DATA subResource = { 0 };
	subResource.pSysMem = vertices;

	//���ؽ� ������ �ʱ�ȭ�� ������ �ѹ��� �̷����
	Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));


	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = sizeof(UINT) * indexCount;

	D3D11_SUBRESOURCE_DATA data;
	data.pSysMem = indices;

	Check(D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer));
}

void Terrain::CreateNormalData()
{
	//�ﰢ�� �ϳ��� �����ϱ����� 3�� �����ش�.
	for (UINT i = 0; i < indexCount / 3; ++i)
	{
		//���� ���� index�� �� ������ ��ȣ�Դϴ�.
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 d1 = vertices[index1].Position - vertices[index0].Position;
		Vector3 d2 = vertices[index2].Position - vertices[index0].Position;

		Vector3 normal;
		D3DXVec3Cross(&normal, &d1, &d2);

		vertices[index0].Normal += normal;
		vertices[index1].Normal += normal;
		vertices[index2].Normal += normal;
	}

	//���� �� for�� ������ ������ �� ���ϰ� �������� �ѹ��� Normalize���ֱ� ����
	for (UINT i = 0; i < vertexCount; ++i)
	{
		D3DXVec3Normalize(&vertices[i].Normal, &vertices[i].Normal);
	}
}
