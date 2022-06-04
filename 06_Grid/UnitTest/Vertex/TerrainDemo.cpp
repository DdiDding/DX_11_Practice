#include "stdafx.h"
#include "TerrainDemo.h"
#include "Environment/Terrain.h"

//��ü �ʱ�ȭ �� ����
void TerrainDemo::Initialize()
{
	shader = new Shader(L"08_Terrain.fx");
	//shader = new Shader(L"06_Grid.fx");
	terrain = new Terrain(shader, L"Terrain/Gray256.png");
}

//�Ҹ���
void TerrainDemo::Destroy()
{

	SafeDelete(terrain);
	SafeDelete(shader);

}

//�� �����Ӹ��� ������ ������Ʈ
void TerrainDemo::Update()
{
	static Vector3 direction = Vector3(1, 1, -1);
	ImGui::SliderFloat3("Direction", direction, -1, 1);
	shader->AsVector("LightDirection")->SetFloatVector(direction);
	terrain->Update();
}

//������ �׸� �ڵ��
void TerrainDemo::Render()
{
	terrain->Render();
}
