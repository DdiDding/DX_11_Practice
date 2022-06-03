#include "Framework.h"
#include "OrbitCam.h"


OrbitCam::OrbitCam()
{
	LookAtPos = Vector3(0, 0, 0);
}

OrbitCam::~OrbitCam()
{
}

void OrbitCam::Update()
{
	if (Mouse::Get()->Press(1) == true)
	{
		Vector3 f = Forward();
		Vector3 u = Up();
		Vector3 r = Right();

		//[Move] 구면좌표계의 중심을 움직임 
		{
			if (Keyboard::Get()->Press('W'))
			{
				LookAtPos = LookAtPos + f * move * Time::Delta();
			}
			if (Keyboard::Get()->Press('S'))
			{
				LookAtPos = LookAtPos - f * move * Time::Delta();
			}


			if (Keyboard::Get()->Press('D'))
			{
				LookAtPos = LookAtPos + r * move * Time::Delta();
			}
			if (Keyboard::Get()->Press('A'))
			{
				LookAtPos = LookAtPos - r * move * Time::Delta();
			}


			if (Keyboard::Get()->Press('Q'))
			{
				LookAtPos = LookAtPos + u * move * Time::Delta();
			}
			if (Keyboard::Get()->Press('E'))
			{
				LookAtPos = LookAtPos - u * move * Time::Delta();
			}

		}
	}

	Vector3 val = Mouse::Get()->GetMoveValue();
	if (Mouse::Get()->Press(1) == true)
	{
		seta += -val.y * rotationSpeed * Time::Delta();
		if (seta < 1.f) seta = 1.f;
		if (179.f < seta) seta = 179.f;

		iongit += -val.x * rotationSpeed * Time::Delta();
		
	}

	radius -= val.z/100;
	if (radius < 1.f) radius = 1.f;

	CalCamPos();
	CalCamRot();

}

void OrbitCam::Speed(float move, float rotation)
{
	this->move = move;
	this->rotationSpeed = rotation;
}

void OrbitCam::CalCamPos()
{
	Vector3 tempPos = Vector3(0, 0, 0);
	tempPos.x = radius * sin(seta * Math::PI / 180.0f) * cos(iongit * Math::PI / 180.0f);
	tempPos.z = radius * sin(seta * Math::PI / 180.0f) * sin(iongit * Math::PI / 180.0f);;
	tempPos.y = radius * cos(seta * Math::PI / 180.0f);

	tempPos.x += LookAtPos.x;
	tempPos.z += LookAtPos.z;
	tempPos.y += LookAtPos.y;
	ImGui::Text("CameraPos.X : %f // CameraPos.Y : %f // CameraPos.Z : %f", tempPos.x, tempPos.y, tempPos.z);
	Position(tempPos);
}

void OrbitCam::CalCamRot()
{
	D3DXVec3Normalize(&forward, &(LookAtPos - position));
	Move();
}
