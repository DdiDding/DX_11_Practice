#pragma once
#include "Systems/IExecute.h"

class Cube : public IExecute {

public:

	// IExecute을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Ready() override {};
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void PreRender() override {};
	virtual void Render() override;
	virtual void PostRender() override {};
	virtual void ResizeScreen() override {};

public:

	void Rotation(const Vector3 & data);
	void Translation(const Vector3 & data);

private:

	void UpdateTransform();

private:

	Shader * shader;

	Vertex vertices[8];
	ID3D11Buffer * vertexBuffer;
	ID3D11Buffer * indexBuffer;

	Matrix world;
	Vector3 r;
	Vector3 t;
};
