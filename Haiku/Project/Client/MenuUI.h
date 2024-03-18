#pragma once
#include "UI.h"


class MenuUI :
    public UI
{

public:
    CGameObject*    m_targetGO;


public:
    CGameObject* GetTargetGO() {return m_targetGO;}

    void SetTargetGO(CGameObject* _GO) { m_targetGO = _GO; }


public:
    virtual void render() override;
    virtual void render_update() override;

private:
    void File();
    void Level();
    void GameObject();
    void Asset();


public:
    MenuUI();
    ~MenuUI();
};

