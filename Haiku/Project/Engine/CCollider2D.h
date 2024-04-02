#pragma once
#include "CComponent.h"

class CCollider2D :
    public CComponent
{
private:
    Vec3    m_Offset;   // 오프셋 포지션
    Vec3    m_FinalPos; // 충돌체의 최종 위치 ( Object Position + Collider offset )

    Vec3    m_Scale;    // 오브젝트로부터 상대적인 배율    
    Vec3    m_Rotation; // 오브젝트로부터 상대적인 회전(자전)

    bool    m_Absolute; // true 인 경우, 오브젝트의 크기에 영향을 받지않는 절대(고정)크기로 계산

    Matrix  m_matColWorld;

    int     m_OverlapCount;

    bool    m_Active;       // 충돌체의 활성화 여부
    bool    m_SemiDeactive; // 비활성화 예정상태

    bool    m_RenderDebugRect; // 콜라이더 네모 그릴지 말지 정하는

    Vec3    m_PrevFinalPos;

public:
    Vec3 GetOffset() { return m_Offset; }
    Vec3 GetScale() { return m_Scale; }
    Vec3 GetFinalPos() { return m_FinalPos; }
    Vec3 GetRotation() { return m_Rotation; }
    float GetRotationZ() { return m_Rotation.z; }

    void SetOffset(Vec3 _Offset) { m_Offset = _Offset; }
    void SetScale(Vec3 _Scale) { m_Scale = _Scale; }
    void SetRotationZ(float _Angle) { m_Rotation.z = _Angle; }
    //void SetRotation(Vec3 _Rot) { m_Rotation = _Rot; }

    const Matrix& GetWorldMat() { return m_matColWorld; }

    void SetAbsolute(bool _Abs) { m_Absolute = _Abs; }
    bool IsAbsolute() { return m_Absolute; }

    void Activate();
    void Deactivate();

    bool IsActive() { return m_Active; }
    bool IsSemiDeactive() { return m_SemiDeactive; }

    void SetRenderDebugRect(bool _b) { m_RenderDebugRect = _b; }
    bool IsRenderDebugRect() { return m_RenderDebugRect;  }

    Vec3 GetPrevFinalPos() { return m_PrevFinalPos; }

public:
    virtual void finaltick() override;

public:
    void BeginOverlap(CCollider2D* _OtherCollider);
    void Overlap(CCollider2D* _OtherCollider);
    void EndOverlap(CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;

public:
    CLONE(CCollider2D);
    CCollider2D();
    CCollider2D(const CCollider2D& _OriginCollider2D);
    ~CCollider2D();

    friend class CTaskMgr;
};

