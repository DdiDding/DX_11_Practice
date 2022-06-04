#include "Framework.h"
#include "Mesh.h"

Mesh::Mesh(Shader * shader)
	: shader(shader)
{
	D3DXMatrixIdentity(&world);

	//이러한 방식으로 넣는것도 있지만 이건 주소를 항상 찾아야한다.
	shader->AsMatrix("World")->SetMatrix(world);
	//그래서 이렇게 주소를 미리 받아두어 사용하는것!
	sWorld = shader->AsMatrix("World");
	sView = shader->AsMatrix("View");
	sProjection = shader->AsMatrix("Projection");
	sColor = shader->AsVector("Color");
}

Mesh::~Mesh()
{
	SafeDeleteArray(vetices);
	SafeDeleteArray(indices);

	SafeRelease(vertexBuffer);
	SafeRelease(indexBuffer);
}

void Mesh::Render()
{
	if (vertexBuffer == NULL || indexBuffer == NULL)
	{
		Create();
		CreateBuffer();
	}

	UINT stride = sizeof(MeshVertex);
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D::GetDC()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, offset);
	D3D::GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	sWorld->SetMatrix(world);
	sView->SetMatrix(Context::Get()->View());
	sProjection->SetMatrix(Context::Get()->Projection());

	shader->DrawIndexed(0, 1, indexCount);
}

void Mesh::Position(float x, float y, float z)
{
	Position(Vector3(x, y, z));
}

void Mesh::Position(Vector3 & vec)
{
	position = vec;
	UpdateWorld();
}

void Mesh::Position(Vector3 * vec)
{
	*vec = position;
}

void Mesh::Rotation(float x, float y, float z)
{
	Rotation(Vector3(x, y, z));
}

void Mesh::Rotation(Vector3 & vec)
{
	rotation = vec;
	UpdateWorld();
}

void Mesh::Rotation(Vector3 * vec)
{
	*vec = rotation;
}

void Mesh::RotationDegree(float x, float y, float z)
{
	RotationDegree(Vector3(x, y, z));
}

void Mesh::RotationDegree(Vector3 & vec)
{
	//rotation = vec * Math::PI / 180.0f;
	rotation = vec * 0.01745238f;
	UpdateWorld();
}

void Mesh::RotationDegree(Vector3 * vec)
{
	*vec = rotation * 57.29577957f;
}

void Mesh::GetWorld(Matrix * matrix)
{
	//*matrix = matView;
	memcpy(matrix, &world, sizeof(Matrix)); //이게 더 빠름
}

void Mesh::Color(float r, float g, float b)
{
	Color(D3DXCOLOR(r, g, b, 1.f));
}

void Mesh::Color(D3DXCOLOR & val)
{
	color = val;
}

Vector3 Mesh::Forward()
{
	return Vector3(world._31, world._32, world._33);
}

Vector3 Mesh::Up()
{
	return Vector3(world._21, world._22, world._23);
}

Vector3 Mesh::Right()
{
	return Vector3(world._11, world._12, world._13);
}

void Mesh::CreateBuffer()
{
	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(MeshVertex) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;

		//버텍스 버퍼의 초기화와 생성이 한번에 이루어짐
		Check(D3D::GetDevice()->CreateBuffer(&desc, &subResource, &vertexBuffer));
	}

	//Create VertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(UINT) * indexCount;

		D3D11_SUBRESOURCE_DATA data;
		data.pSysMem = indices;

		Check(D3D::GetDevice()->CreateBuffer(&desc, &data, &indexBuffer));
	}
}

void Mesh::UpdateWorld()
{
	Matrix S, R, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);
	D3DXMatrixRotationYawPitchRoll(&R, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&T, position.x, position.y, position.z);

	world = S * R * T;

}
