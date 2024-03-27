#include "pch.h"
#include "CMovement.h"


CMovement::CMovement()
	: CComponent(COMPONENT_TYPE::MOVEMENT)
{
}

CMovement::~CMovement()
{
}


void CMovement::finaltick()
{
}

void CMovement::UpdateData()
{
}

void CMovement::SaveToFile(FILE* _File)
{
}

void CMovement::LoadFromFile(FILE* _File)
{
}
