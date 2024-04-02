#pragma once
#include <Engine\CState.h>
class CHaikuDashState :
    public CState
{
private:
    float duration; // �󸶵��� ��ð� ����Ǿ�� �ϴ���
    float accTime; // ���� ���� ��� �ð�

    float dashLength; // ��� �Ÿ�
    float dashSpeed; // ��� ���ǵ�

    Vec3 afterDashPos; // ��� �� ������ ������

public:
    void DashSet();

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuDashState();
    ~CHaikuDashState();
};

