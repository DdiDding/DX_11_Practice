#include "stdafx.h"
#include "TerrainDemo.h"
#include "Environment/Terrain.h"

//객체 초기화 및 생성
void TerrainDemo::Initialize()
{
	shader = new Shader(L"08_Terrain.fx");
	//shader = new Shader(L"06_Grid.fx");
	terrain = new Terrain(shader, L"Terrain/Gray256.png");
}

//소멸자
void TerrainDemo::Destroy()
{

	SafeDelete(terrain);
	SafeDelete(shader);

}

//매 프레임마다 데이터 업데이트
void TerrainDemo::Update()
{
	static Vector3 direction = Vector3(1, 1, -1);
	ImGui::SliderFloat3("Direction", direction, -1, 1);
	shader->AsVector("LightDirection")->SetFloatVector(direction);
	terrain->Update();
}

//실제로 그릴 코드들
void TerrainDemo::Render()
{
	terrain->Render();
}
