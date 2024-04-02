#include "pch.h"
#include "CHaikuScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CMovement.h>

#include <Engine/CCollisionMgr.h>
#include "CPlatformScript.h"


CHaikuScript::CHaikuScript()
	: CScript(HAIKUSCRIPT)
	, curDir(false)
	, prevDir(false)
	, curStateName(L"Start")
	, prevStateName(L"Start")
	, prevColDir(COLLISION_DIR::NONE)
	, collisionCnt(0)
{
}

CHaikuScript::~CHaikuScript()
{
}

void CHaikuScript::begin()
{

	if (nullptr != StateMachine()->GetFSM())
	{
		StateMachine()->GetDynamicFSM()->ChangeState(L"Start");
	}

	// �浹 ����
	CCollisionMgr::GetInst()->LayerCheck(4, 2); // ������ & �÷���
}

void CHaikuScript::tick()
{
	if (KEY_TAP(KEY::LEFT))
	{
		curDir = true; // ���� ����
		Animator2D()->Play(L"haiku_walk");
	}

	if ((KEY_TAP(KEY::RIGHT)))
	{
		curDir = false; // ���� ������
		Animator2D()->Play(L"haiku_walk");
	}

	if (KEY_PRESSED(KEY::LEFT)) //������ �ƴ� ����
	{
		Movement()->AddForce(Vec3(-300.f, 0.f, 0.f) * DT);
	}

	if ((KEY_PRESSED(KEY::RIGHT)))
	{
		Movement()->AddForce(Vec3(300.f, 0.f, 0.f) * DT);
	}

	if (KEY_RELEASED(KEY::LEFT))
	{
		Movement()->SetVelocity(Vec3());
		if (!(KEY_PRESSED(KEY::RIGHT)))
		{
			Animator2D()->Play(L"haiku_idle");
		}

	}

	if ((KEY_RELEASED(KEY::RIGHT)))
	{
		Movement()->SetVelocity(Vec3());
		if (!(KEY_PRESSED(KEY::LEFT)))
		{
			Animator2D()->Play(L"haiku_idle");
		}
	}

	if (prevDir != curDir) // ����� ������ ������ �޶��ٸ�
	{
		float x = Transform()->GetRelativeScale().x * -1;
		Vec3 vPos = Vec3(Transform()->GetRelativeScale().x * -1, Transform()->GetRelativeScale().y, Transform()->GetRelativeScale().z);
		Transform()->SetRelativeScale(vPos);
	}

	prevDir = curDir;
}

// =====================================================================================================================


void CHaikuScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

	if (2 == _OtherObj->GetLayerIdx())
	{
		colPlatformName = _OtherObj->GetName();

	}
}

void CHaikuScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CHaikuScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	

	colPlatformName = L"";
}

void CHaikuScript::SaveToFile(FILE* _File)
{
}

void CHaikuScript::LoadFromFile(FILE* _File)
{
}

void CHaikuScript::AddOverlapGround(CGameObject* _pObejct)
{
	m_Ground.push_back(_pObejct);

	m_OverlapGround = m_Ground.size();
}

void CHaikuScript::SubOverlapGround(CGameObject* _pObejct)
{
	vector<CGameObject*>::iterator iter = m_Ground.begin();

	for (; iter != m_Ground.end();)
	{
		if (*iter == _pObejct)
		{
			iter = m_Ground.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	m_OverlapGround = m_Ground.size();
}