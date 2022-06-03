#pragma once
#include "Systems/IExecute.h"

class GridDemo : public IExecute {

	// IExecute을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Ready() override {};
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

private:

	Shader * shader;

	UINT width = 5;
	UINT height = 5;

	UINT vertexCount;
	Vertex * vertices;
	ID3D11Buffer * vertexBuffer;

	UINT indexCount;
	UINT * indices;
	ID3D11Buffer * indexBuffer;

	Matrix world;
};
