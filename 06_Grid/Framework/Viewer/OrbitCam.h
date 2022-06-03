#pragma once
#include "Camera.h"

class OrbitCam : public Camera
{
public:
	OrbitCam();
	~OrbitCam();

	virtual void Update() override;

	void Speed(float move, float rotation);


private:

	Vector3 LookAtPos;

	float radius = 100.f;
	float seta = 0.f;
	float iongit = 0.f;

	//Speed
	float move = 20.f;
	float rotationSpeed = 2.0f;
};