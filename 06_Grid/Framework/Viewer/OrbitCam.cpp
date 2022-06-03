#include "Framework.h"
#include "OrbitCam.h"

OrbitCam::OrbitCam()
{

}

OrbitCam::~OrbitCam()
{
}

void OrbitCam::Update()
{
	if (Mouse::Get()->Press(1) == false) return;

	Vector3 f = Forward();
	Vector3 u = Up();
	Vector3 r = Right();

	//Move
	{
		Vector3 P;
		Position(&P);

		if (Keyboard::Get()->Press('W'))
		{
			P = P + f * move * Time::Delta();
		}
		if (Keyboard::Get()->Press('S'))
		{
			P = P - f * move * Time::Delta();
		}


		if (Keyboard::Get()->Press('D'))
		{
			P = P + r * move * Time::Delta();
		}
		if (Keyboard::Get()->Press('A'))
		{
			P = P - r * move * Time::Delta();
		}


		if (Keyboard::Get()->Press('Q'))
		{
			P = P + u * move * Time::Delta();
		}
		if (Keyboard::Get()->Press('E'))
		{
			P = P - u * move * Time::Delta();
		}

		Position(P);
	}

	//Rotation
	{
		Vector3 R;
		Rotation();

		Vector3 val = Mouse::Get()->GetMoveValue();
		iongit += val.y * rotationSpeed * Time::Delta();
		seta += val.x * rotationSpeed * Time::Delta();
		R.z = 0.0f;

		Rotation(&R);
	}
}

void OrbitCam::Speed(float move, float rotation)
{
	this->move = move;
	this->rotationSpeed = rotation;
}
