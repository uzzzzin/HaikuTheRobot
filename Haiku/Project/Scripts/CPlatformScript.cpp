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
	if (4 == _OtherObj->GetLayerIdx()) // 얘가 하이쿠일 때
	{
		//Vec3 PlatformPos, float PlatformWidth, float PlatformHeight, Vec3 ObjPos, float ObjWidth, float ObjHeight
		curColDir = DetectCollision(Transform()->GetRelativePos(), Transform()->GetRelativeScale().x, Transform()->GetRelativeScale().y, _OtherCollider->GetFinalPos(), _OtherCollider->GetScale().x, _OtherCollider->GetScale().y);
	}
}

void CPlatformScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (4 == _OtherObj->GetLayerIdx()) // 얘가 하이쿠일 때
	{
		switch (curColDir)
		{
		case COLLISION_DIR::UP: // 하이쿠가 천장박음
			// 위쪽 충돌
			break;
		case COLLISION_DIR::DOWN: // 하이쿠가 플랫폼을 밟고 있음
		{
			float y1 = Transform()->GetRelativePos().y + Transform()->GetRelativeScale().y / 2;

			float y2 = _OtherCollider->GetFinalPos().y - _OtherCollider->GetScale().y / 2;

			float y3 = y1 - y2;

			Vec3 v = Vec3(_OtherObj->Transform()->GetRelativePos().x, _OtherObj->Transform()->GetRelativePos().y + y3, _OtherObj->Transform()->GetRelativePos().z);

			_OtherObj->Transform()->SetRelativePos(v);
		}
			break;
		case COLLISION_DIR::LEFT: // 왼쪽에서 쿵
			// 왼쪽 충돌
			break;
		case COLLISION_DIR::RIGHT: // 오른쪽에서 쿵
			// 오른쪽 충돌
			break;
		case COLLISION_DIR::NONE: // 들어오면 사고
			break;
		}
	}
	

	//if (4 == _OtherObj->GetLayerIdx()) // 얘가 하이쿠일 때
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
	// 콜라이더 크기 절반
	float halfPlatformWidth = PlatformWidth * 0.5f;
	float halfPlatformHeight = PlatformHeight * 0.5f;
	float halfObjWidth = ObjWidth * 0.5f;
	float halfObjHeight = ObjHeight * 0.5f;

	// 충돌 지점에서의 상대 위치 계산
	float relativeX = ObjPos.x - PlatformPos.x;
	float relativeY = ObjPos.y - PlatformPos.y;

	// 두 축에 대한 오버랩 계산
	float xOverlap = halfObjWidth + halfPlatformWidth - abs(relativeX);
	float yOverlap = halfObjHeight + halfPlatformHeight - abs(relativeY);

	// 충돌 여부 확인
	if (xOverlap > 0 && yOverlap > 0) 
	{
		// x축과 y축 중 어느 축에서 오버랩이 더 큰지 확인하여 충돌 방향 결정
		if (xOverlap < yOverlap) 
		{
			// 좌우 충돌
			if (relativeX < 0) 
			{
				// 플랫폼의 왼쪽에서 충돌
				// 좌측 충돌
				return COLLISION_DIR::LEFT;
			}
			else 
			{
				// 플랫폼의 오른쪽에서 충돌
				// 우측 충돌
				return COLLISION_DIR::RIGHT;
			}
		}
		else {
			// 위아래 충돌
			if (relativeY < 0) 
			{
				// 플랫폼의 위에서 충돌
				// 상단 충돌
				return COLLISION_DIR::UP;
			}
			else 
			{
				// 플랫폼의 아래에서 충돌
				// 하단 충돌
				return COLLISION_DIR::DOWN;
			}
		}
	}

	// 충돌이 없는 경우
	return COLLISION_DIR::NONE;
}
