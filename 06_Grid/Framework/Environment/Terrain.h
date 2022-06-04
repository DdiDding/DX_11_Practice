#pragma once

class Terrain
{
public:
	typedef VertexNormal TerrainVertex;

	Terrain(Shader * shader, wstring heightFile);
	~Terrain();

	void Update();
	void Render();

	void Pass(UINT val) { pass = val; }

private:
	void CreateVertexData();
	void CreateIndexData();
	void CreateBuffer();
	void CreateNormalData();
private:
	int pass = 0;
	Texture * heightMap;
	Shader * shader;

	//텍스쳐에서 불러옴
	UINT width;
	UINT height;

	UINT vertexCount;
	TerrainVertex * vertices;
	ID3D11Buffer * vertexBuffer;

	UINT indexCount;
	UINT * indices;
	ID3D11Buffer * indexBuffer;
};