#include "pch.h"
#include "CPlatformScript.h"


CPlatformScript::CPlatformScript()
	:CScript(PLATFORMSCRIPT)
	, curColDir(COLLISION_DIR::NONE)
{
}

CPlatformScript::~CPlatformScript()
{
}

void CPlatformScript::begin()
{
}

void CPlatformScript::tick()
{

}

void CPlatformScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (4 == _OtherObj->GetLayerIdx()) // �갡 �������� ��
	{
		//Vec3 PlatformPos, float PlatformWidth, float PlatformHeight, Vec3 ObjPos, float ObjWidth, float ObjHeight
		curColDir = DetectCollision(Transform()->GetRelativePos(), Transform()->GetRelativeScale().x, Transform()->GetRelativeScale().y, _OtherCollider->GetFinalPos(), _OtherCollider->GetScale().x, _OtherCollider->GetScale().y);
	}
}

void CPlatformScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (4 == _OtherObj->GetLayerIdx()) // �갡 �������� ��
	{
		switch (curColDir)
		{
		case COLLISION_DIR::UP: // ������ õ�����
			// ���� �浹
			break;
		case COLLISION_DIR::DOWN: // ������ �÷����� ��� ����
		{
			float y1 = Transform()->GetRelativePos().y + Transform()->GetRelativeScale().y / 2;

			float y2 = _OtherCollider->GetFinalPos().y - _OtherCollider->GetScale().y / 2;

			float y3 = y1 - y2;

			Vec3 v = Vec3(_OtherObj->Transform()->GetRelativePos().x, _OtherObj->Transform()->GetRelativePos().y + y3, _OtherObj->Transform()->GetRelativePos().z);

			_OtherObj->Transform()->SetRelativePos(v);
		}
			break;
		case COLLISION_DIR::LEFT: // ���ʿ��� ��
			// ���� �浹
			break;
		case COLLISION_DIR::RIGHT: // �����ʿ��� ��
			// ������ �浹
			break;
		case COLLISION_DIR::NONE: // ������ ���
			break;
		}
	}
	

	//if (4 == _OtherObj->GetLayerIdx()) // �갡 �������� ��
	//{
		//float y1 = Transform()->GetRelativePos().y + Transform()->GetRelativeScale().y / 2;

		//float y2 = _OtherCollider->GetFinalPos().y - _OtherCollider->GetScale().y / 2;

		//float y3 = y1 - y2;

		//Vec3 v = Vec3(_OtherObj->Transform()->GetRelativePos().x, _OtherObj->Transform()->GetRelativePos().y + y3, _OtherObj->Transform()->GetRelativePos().z);

		//_OtherObj->Transform()->SetRelativePos(v);
	//}
}

void CPlatformScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	curColDir = COLLISION_DIR::NONE;
}

void CPlatformScript::SaveToFile(FILE* _File)
{
}

void CPlatformScript::LoadFromFile(FILE* _File)
{
}

COLLISION_DIR CPlatformScript::DetectCollision(Vec3 PlatformPos, float PlatformWidth, float PlatformHeight, Vec3 ObjPos, float ObjWidth, float ObjHeight)
{
	// �ݶ��̴� ũ�� ����
	float halfPlatformWidth = PlatformWidth * 0.5f;
	float halfPlatformHeight = PlatformHeight * 0.5f;
	float halfObjWidth = ObjWidth * 0.5f;
	float halfObjHeight = ObjHeight * 0.5f;

	// �浹 ���������� ��� ��ġ ���
	float relativeX = ObjPos.x - PlatformPos.x;
	float relativeY = ObjPos.y - PlatformPos.y;

	// �� �࿡ ���� ������ ���
	float xOverlap = halfObjWidth + halfPlatformWidth - abs(relativeX);
	float yOverlap = halfObjHeight + halfPlatformHeight - abs(relativeY);

	// �浹 ���� Ȯ��
	if (xOverlap > 0 && yOverlap > 0) 
	{
		// x��� y�� �� ��� �࿡�� �������� �� ū�� Ȯ���Ͽ� �浹 ���� ����
		if (xOverlap < yOverlap) 
		{
			// �¿� �浹
			if (relativeX < 0) 
			{
				// �÷����� ���ʿ��� �浹
				// ���� �浹
				return COLLISION_DIR::LEFT;
			}
			else 
			{
				// �÷����� �����ʿ��� �浹
				// ���� �浹
				return COLLISION_DIR::RIGHT;
			}
		}
		else {
			// ���Ʒ� �浹
			if (relativeY < 0) 
			{
				// �÷����� ������ �浹
				// ��� �浹
				return COLLISION_DIR::UP;
			}
			else 
			{
				// �÷����� �Ʒ����� �浹
				// �ϴ� �浹
				return COLLISION_DIR::DOWN;
			}
		}
	}

	// �浹�� ���� ���
	return COLLISION_DIR::NONE;
}
