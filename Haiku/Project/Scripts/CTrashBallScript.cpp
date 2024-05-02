#include "pch.h"
#include "CTrashBallScript.h"

CTrashBallScript::CTrashBallScript()
	: CScript(TRASHBALLSCRIPT)
    , bWillDestroy(false)
{
}

CTrashBallScript::~CTrashBallScript()
{
}

void CTrashBallScript::begin()
{
    GetRenderComponent()->GetDynamicMaterial();

    fRandomSpawnX = SetRandomSpawnX();

    Transform()->SetRelativePos(Vec3(fRandomSpawnX, 43.f, -5.f));

    Collider2D()->Activate();
    StateMachine()->GetDynamicFSM()->ChangeState(L"Spawn");
}

void CTrashBallScript::tick()
{
}

void CTrashBallScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
    if (2 == _OtherObj->GetLayerIdx())
    {
        bWillDestroy = true; // ∂•ø° ¥Íæ“¿∏¥œ º“∏Í«’Ω√¥Ÿ
    }
}

void CTrashBallScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CTrashBallScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CTrashBallScript::SaveToFile(FILE* _File)
{
}

void CTrashBallScript::LoadFromFile(FILE* _File)
{
}

float CTrashBallScript::SetRandomSpawnX()
{
    static bool initialized = false;
    if (!initialized) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        initialized = true;
    }

    return 1291.0f + static_cast<float>(std::rand()) / RAND_MAX * (1564.0f - 1291.0f);
}