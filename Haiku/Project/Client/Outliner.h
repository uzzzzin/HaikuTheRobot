#pragma once
#include "UI.h"

// ���� ������ �ִ� ��� ������Ʈ�� ����

class TreeUI;
class TreeNode;

class Outliner :
    public UI
{
private:
    TreeUI*     m_Tree;

    bool    m_bRightClick;

public:
    virtual void render_update() override;

public:
    void ResetCurrentLevel();

private:
    void AddObjectToTree(TreeNode* _Node, CGameObject* _Object);
    void SelectObject(DWORD_PTR _Node);
    void DragDropObject(DWORD_PTR _Dest, DWORD_PTR _Source);

public:
    void DrawRightClickMenu();
    void DeleteObject();

public:
    void OpenRightClickMenu() { m_bRightClick = true; };

public:
    Outliner();
    ~Outliner();
};

