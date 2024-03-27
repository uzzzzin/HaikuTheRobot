#pragma once
#include "CComponent.h"
class CMovement :
    public CComponent
{

public:
    virtual void finaltick() override;
    virtual void UpdateData() override;



public:
    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CMovement);
public:
    CMovement();
    ~CMovement();

};

