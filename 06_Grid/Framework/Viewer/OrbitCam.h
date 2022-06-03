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

	float radius = 100.f;
	

	//Speed
	float move = 20.f;
	float rotation = 2.0f;
};