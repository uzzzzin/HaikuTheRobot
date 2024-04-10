#include "pch.h"
#include "ParticleSystemUI.h"

#include <Engine/CParticleSystem.h>

ParticleSystemUI::ParticleSystemUI() 
	: ComponentUI("ParticleSystem", "##ParticleSystem", COMPONENT_TYPE::PARTICLESYSTEM)
{
	//SetSize(ImVec2(0.f, 300.f));
	SetComopnentTitle("ParticleSystem");
}

ParticleSystemUI::~ParticleSystemUI()
{
}


void ParticleSystemUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	//string texName = ToString(SetParticleTexture());

	string textureName = ToString(GetTargetObject()->ParticleSystem()->GetParticleTexFileName());
	ImGui::Text(textureName.c_str());

	if (ImGui::Button(u8"Texture 변경", ImVec2(110, 25)))
	{
		SetParticleTexture();
	}

	tParticleModule tModule = GetTargetObject()->ParticleSystem()->GetParticleModule();

	// Module On/Off Check
	bool bSpawn = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN];
	bool bAddVelocity = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY];
	bool bScale = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::SCALE];
	bool bNoiseForce = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE];
	bool bDrag = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::DRAG];
	bool bCalculateForce = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::CALCULATE_FORCE];
	bool bRender = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::RENDER];

	ImGui::Text("Spawn");
	ImGui::SameLine(100);
	ImGui::Checkbox("##Spawn", &bSpawn);
	ImGui::Text("Add Velocity");
	ImGui::SameLine(100);
	ImGui::Checkbox("##Add Velocity", &bAddVelocity);
	ImGui::Text("Scale");
	ImGui::SameLine(100);
	ImGui::Checkbox("##Scale", &bScale);
	ImGui::Text("NoiseForce");
	ImGui::SameLine(100);
	ImGui::Checkbox("##NoiseForce", &bNoiseForce);
	ImGui::Text("Drag");
	ImGui::SameLine(100);
	ImGui::Checkbox("##Drag", &bDrag);
	ImGui::Text("CalculateForce");
	ImGui::SameLine(100);
	ImGui::Checkbox("##CalculateForce", &bCalculateForce);
	ImGui::Text("Render");
	ImGui::SameLine(100);
	ImGui::Checkbox("##Render", &bRender);

	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN] = bSpawn;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = bAddVelocity;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::SCALE] = bScale;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = bNoiseForce;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = bDrag;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::CALCULATE_FORCE] = bCalculateForce;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = bRender;


	if (true == bSpawn)
	{
		ImGui::SeparatorText("Spawn"); // -------------------------------------

		ImGui::Text(u8"vSpawnColor 초기 컬러");
		ImGui::SameLine();
		ImGui::DragFloat4("##vSpawnColor", tModule.vSpawnColor);

		ImGui::Text(u8"vSpawnMinScale 초기 최소 크기");
		ImGui::SameLine();
		ImGui::DragFloat4("##vSpawnMinScale", tModule.vSpawnMinScale);

		ImGui::Text(u8"vSpawnMaxScale 초기 최대 크기");
		ImGui::SameLine();
		ImGui::DragFloat4("##vSpawnMaxScale", tModule.vSpawnMaxScale);

		ImGui::Text(u8"MinLife 최소 수명");
		ImGui::SameLine();
		ImGui::DragFloat("##MinLife", &tModule.MinLife);

		ImGui::Text(u8"MaxLife 최대 수명");
		ImGui::SameLine();
		ImGui::DragFloat("##MaxLife", &tModule.MaxLife);

		ImGui::Text(u8"MinMass 최소 질량");
		ImGui::SameLine();
		ImGui::DragFloat("##MinMass", &tModule.MinMass);

		ImGui::Text(u8"MaxMass 최대 질량");
		ImGui::SameLine();
		ImGui::DragFloat("##MaxMass", &tModule.MaxMass);

		ImGui::Text(u8"SpawnRate 초당 생성 개수");
		ImGui::SameLine();
		ImGui::DragInt("##SpawnRate", &tModule.SpawnRate);

		ImGui::Text(u8"SpaceType 좌표계(0 : LocalSpace, 1 : WorldSpace)");
		ImGui::SameLine();
		ImGui::DragInt("##SpaceType", &tModule.SpaceType);

		ImGui::Text(u8"SpawnShape 스폰 범위(0 : Sphere, 1 : Box)");
		ImGui::SameLine();
		ImGui::DragInt("##SpawnShape", &tModule.SpawnShape);

		ImGui::Text(u8"Radius SpawnShape = Sphere => 반지름 길이");
		ImGui::SameLine();
		ImGui::DragFloat("##Radius", &tModule.Radius);

		ImGui::Text(u8"vSpawnBoxScale SpawnShape = Box => Box 크기");
		ImGui::SameLine();
		ImGui::DragFloat4("##vSpawnBoxScale", tModule.vSpawnBoxScale);
	}

	if (true == bAddVelocity)
	{
		ImGui::SeparatorText("Add Velocity"); // ------------------------------------------

		ImGui::Text(u8"AddVelocityType0 : From Center, 1: To Center, 2: Fix Direction");
		ImGui::SameLine();
		ImGui::DragInt("##AddVelocityType", &tModule.AddVelocityType);

		ImGui::Text(u8"MinSpeed 최소 속도");
		ImGui::SameLine();
		ImGui::DragFloat("##MinSpeed", &tModule.MinSpeed);

		ImGui::Text(u8"MaxSpeed 최대 속도");
		ImGui::SameLine();
		ImGui::DragFloat("##MaxSpeed", &tModule.MaxSpeed);

		ImGui::Text(u8"FixedAngle 해당 방향에서 랜덤범위 각도");
		ImGui::SameLine();
		ImGui::DragFloat("##FixedAngle", &tModule.FixedAngle);

		ImGui::Text(u8"FixedDirection 지정 방향");
		ImGui::SameLine();
		ImGui::DragFloat4("##FixedDirection", tModule.FixedDirection);
	}
	
	if (true == bScale)
	{
		ImGui::SeparatorText("Scale"); // ------------------------------------------

		ImGui::Text(u8"vScaleRatio");
		ImGui::SameLine();
		ImGui::DragFloat4("##vScaleRatio", tModule.vScaleRatio);
	}

	if (true == bNoiseForce)
	{
		ImGui::SeparatorText("Noise Force"); // ------------------------------------------

		ImGui::Text(u8"NoiseForceScale");
		ImGui::SameLine();
		ImGui::DragFloat("##NoiseForceScale", &tModule.NoiseForceScale);

		ImGui::Text(u8"NoiseForceTerm");
		ImGui::SameLine();
		ImGui::DragFloat("##NoiseForceTerm", &tModule.NoiseForceTerm);
	}

	if (true == bDrag)
	{
		ImGui::SeparatorText("Drag"); // ------------------------------------------

		ImGui::Text(u8"DragTime 감속하는데에 걸리는 시간");
		ImGui::SameLine();
		ImGui::DragFloat("##DragTime", &tModule.DragTime);
	}

	if (true == bCalculateForce)
	{
		ImGui::SeparatorText("Render"); // ------------------------------------------

		ImGui::Text(u8"VelocityAlignment => 1 : On, 0 : Off");
		ImGui::SameLine();
		ImGui::DragInt("##VelocityAlignment", &tModule.VelocityAlignment);

		ImGui::Text(u8"AlphaBasedLife => 0 : off, 1 : NomrlizedAge, 2: Age");
		ImGui::SameLine();
		ImGui::DragInt("##AlphaBasedLife", &tModule.AlphaBasedLife);

		ImGui::Text(u8"AlphaMaxAge");
		ImGui::SameLine();
		ImGui::DragFloat("##AlphaMaxAge", &tModule.AlphaMaxAge);
	}

	//ImGui::SeparatorText("Module On / Off"); // ------------------------------------------
	//ImGui::Text(u8"으이?");

	GetTargetObject()->ParticleSystem()->SetParticleModule(tModule);
}

void ParticleSystemUI::SetParticleTexture()
{
	wstring fileName;

	// 파일 탐색기
	wchar_t szFilePath[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFile = sizeof(szFilePath);
	ofn.lpstrFilter = L"ALL\0*.*\0texture\0particle\0*.png";
	ofn.nFilterIndex = 1;

	wstring strInitPath = CPathMgr::GetContentPath();
	strInitPath += L"texture\\particle\\";
	ofn.lpstrInitialDir = strInitPath.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		fileName = ofn.lpstrFile;
		size_t pos = fileName.find_last_of(L"\\");
		if (pos != wstring::npos)
		{
			fileName = fileName.substr(pos + 1);
		}
	}
	GetTargetObject()->ParticleSystem()->SetParticleTexture(L"texture\\particle\\" + fileName);
}