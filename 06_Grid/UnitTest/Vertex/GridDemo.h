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

	int width = 5;
	int height = 5;

	Vertex vertices[6];
	ID3D11Buffer * vertexBuffer;

	UINT indecies[6];
	ID3D11Buffer * indexBuffer;
};
