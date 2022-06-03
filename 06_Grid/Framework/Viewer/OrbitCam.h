#pragma once
#include "Camera.h"

class OrbitCam : public Camera
{
public:
	OrbitCam();
	~OrbitCam();

	virtual void Update() override;
	void Speed(float move, float rotation);
	virtual Vector3 GetLookPos() final { return LookAtPos; }


private:
	void CalCamPos();
	void CalCamRot();

private:

	//������ǥ���� �߽�
	Vector3 LookAtPos;

	//������ǥ���� �� ��ǥ
	float radius = 10.f;
	float seta = 0.f;
	float iongit = 0.f;

	//Speed
	float move = 20.f;
	float rotationSpeed = 100.0f;

	bool bDebugMode{ false };
};