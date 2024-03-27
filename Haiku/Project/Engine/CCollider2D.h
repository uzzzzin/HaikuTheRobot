#pragma once
#include "CComponent.h"

class CCollider2D :
    public CComponent
{
private:
    Vec3    m_Offset;   // ������ ������
    Vec3    m_FinalPos; // �浹ü�� ���� ��ġ ( Object Position + Collider offset )

    Vec3    m_Scale;    // ������Ʈ�κ��� ������� ����    
    Vec3    m_Rotation; // ������Ʈ�κ��� ������� ȸ��(����)

    bool    m_Absolute; // true �� ���, ������Ʈ�� ũ�⿡ ������ �����ʴ� ����(����)ũ��� ���

    Matrix  m_matColWorld;

    int     m_OverlapCount;

    bool    m_Active;       // �浹ü�� Ȱ��ȭ ����
    bool    m_SemiDeactive; // ��Ȱ��ȭ ��������

    bool    m_RenderDebugRect; // �ݶ��̴� �׸� �׸��� ���� ���ϴ�

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

