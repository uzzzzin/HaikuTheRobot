#include "pch.h"
#include "MenuUI.h"



#include <Engine/CPathMgr.h>
#include <Engine/CTaskMgr.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CScriptMgr.h>
#include <Engine/CScript.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include "CLevelSaveLoad.h"



MenuUI::MenuUI()
	: UI("Menu", "##Menu")
    , m_targetGO (nullptr)
{
}

MenuUI::~MenuUI()
{
}

void MenuUI::render()
{
    if (ImGui::BeginMainMenuBar())
    {     
        render_update();

        ImGui::EndMainMenuBar();
    }
}

void MenuUI::render_update()
{
    File();

    Level();

    GameObject();
    
    Asset();
}

void MenuUI::File()
{
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Save Level", ""))
        {
            wchar_t szSelect[256] = {};

            OPENFILENAME ofn = {};

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFile = szSelect;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szSelect);
            ofn.lpstrFilter = L"ALL\0*.*\0Level\0*.lv";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;

            // 탐색창 초기 위치 지정
            wstring strInitPath = CPathMgr::GetContentPath();
            strInitPath += L"level\\";
            ofn.lpstrInitialDir = strInitPath.c_str();

            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetSaveFileName(&ofn))
            {                
                CLevelSaveLoad::SaveLevel(CLevelMgr::GetInst()->GetCurrentLevel(), CPathMgr::GetRelativePath(szSelect));
            }
        }

        if (ImGui::MenuItem("Load Level", ""))
        {
            wchar_t szSelect[256] = {};

            OPENFILENAME ofn = {};

            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = nullptr;
            ofn.lpstrFile = szSelect;
            ofn.lpstrFile[0] = '\0';
            ofn.nMaxFile = sizeof(szSelect);
            ofn.lpstrFilter = L"ALL\0*.*\0Level\0*.lv";
            ofn.nFilterIndex = 1;
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;

            // 탐색창 초기 위치 지정
            wstring strInitPath = CPathMgr::GetContentPath();
            strInitPath += L"level\\";
            ofn.lpstrInitialDir = strInitPath.c_str();

            ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            if (GetOpenFileName(&ofn))
            {                
                CLevel* pLevel = CLevelSaveLoad::LoadLevel(CPathMgr::GetRelativePath(szSelect));
                CLevelMgr::GetInst()->ChangeLevel(pLevel, LEVEL_STATE::STOP);

                // Inspector 의 타겟정보를 nullptr 로 되돌리기
                Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
                pInspector->SetTargetObject(nullptr);
            }
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Level()
{
    if (ImGui::BeginMenu("Level"))
    {
        CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

        LEVEL_STATE State = pCurLevel->GetState();

        bool PlayEnable = false;
        bool PauseEnable = false;
        bool StopEnable = false;

        if (LEVEL_STATE::STOP == State || LEVEL_STATE::PAUSE == State)
            PlayEnable = true;
        else
            PlayEnable = false;

        if (LEVEL_STATE::PLAY == State)
            PauseEnable = true;
        else
            PauseEnable = false;

        if (LEVEL_STATE::PLAY == State || LEVEL_STATE::PAUSE == State)
            StopEnable = true;
        else
            StopEnable = false;

        
        if (ImGui::MenuItem("Play", nullptr, nullptr, PlayEnable))
        {   
            if (LEVEL_STATE::STOP == pCurLevel->GetState())
            {
                CLevelSaveLoad::SaveLevel(pCurLevel, L"Level//temp.lv");
            }
            
            CLevelMgr::GetInst()->ChangeLevelState(LEVEL_STATE::PLAY);
        }

        if (ImGui::MenuItem("Pause", nullptr, nullptr, PauseEnable))
        {
            CLevelMgr::GetInst()->ChangeLevelState(LEVEL_STATE::PAUSE);
        }

        if (ImGui::MenuItem("Stop", nullptr, nullptr, StopEnable))
        {
            CLevel* pLoadedLevel = CLevelSaveLoad::LoadLevel(L"Level//temp.lv");
            CLevelMgr::GetInst()->ChangeLevel(pLoadedLevel, LEVEL_STATE::STOP);

            // Inspector 의 타겟정보를 nullptr 로 되돌리기
            Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
            pInspector->SetTargetObject(nullptr);
        }

        ImGui::EndMenu();
    }
}

void MenuUI::GameObject()
{
    if (ImGui::BeginMenu("GameObject"))
    {
        if (ImGui::MenuItem("Delete Target Object", ""))
        {
            m_targetGO->Destroy();
        }

        ImGui::Separator();

        if (ImGui::BeginMenu("Create Empty Object", ""))
        {
            if (ImGui::BeginMenu("SetName"))
            {
                static char textBuffer[256] = "";
                ImGui::InputText("##GOName", textBuffer, IM_ARRAYSIZE(textBuffer));

               if (ImGui::Button("create"))
               {
                   string str(textBuffer);
                   wstring GOname = ToWString(str);
                   CGameObject* pNewObj = new CGameObject;
                   pNewObj->SetName(GOname);
                   pNewObj->AddComponent(new CTransform);
                   GamePlayStatic::SpawnGameObject(pNewObj, 0);
                   m_targetGO = pNewObj;
               }
               ImGui::EndMenu(); // Set Go Name
            }
            ImGui::EndMenu();
        }

        ImGui::Separator();

        if (ImGui::BeginMenu("Component", ""))
        {

            if (ImGui::BeginMenu("Transform"))
            {
                if(ImGui::MenuItem(u8"추가"))
                {
                    // 만약 오브젝트가 트랜스폼 안 들고 있으면 추가
                    if(nullptr == m_targetGO->GetComponent(COMPONENT_TYPE::TRANSFORM))
                        m_targetGO->AddComponent(new CTransform);
                }

                ImGui::MenuItem(u8"삭제");

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Collider2D"))
            {
                if (ImGui::MenuItem(u8"추가"))
                {
                    if (nullptr == m_targetGO->GetComponent(COMPONENT_TYPE::COLLIDER2D))
                        m_targetGO->AddComponent(new CCollider2D);
                }

                if (ImGui::MenuItem(u8"삭제"))
                {

                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Animator2D"))
            {
                if (ImGui::MenuItem(u8"추가"))
                {
                    if (nullptr == m_targetGO->GetComponent(COMPONENT_TYPE::ANIMATOR2D))
                        m_targetGO->AddComponent(new CAnimator2D);
                }

                if (ImGui::MenuItem(u8"삭제"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Light2D"))
            {
                if (ImGui::MenuItem(u8"추가"))
                {
                    if (nullptr == m_targetGO->GetComponent(COMPONENT_TYPE::LIGHT2D))
                        m_targetGO->AddComponent(new CLight2D);
                }

                if (ImGui::MenuItem(u8"삭제"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Camera"))
            {
                if (ImGui::MenuItem(u8"추가"))
                {
                    if (nullptr == m_targetGO->GetComponent(COMPONENT_TYPE::CAMERA))
                        m_targetGO->AddComponent(new CCamera);
                }

                if (ImGui::MenuItem(u8"삭제"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("StateMachine(FSM)"))
            {
                if (ImGui::MenuItem(u8"추가"))
                {
                    if (nullptr == m_targetGO->GetComponent(COMPONENT_TYPE::STATEMACHINE))
                        m_targetGO->AddComponent(new CStateMachine);
                }

                if (ImGui::MenuItem(u8"삭제"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("(RC)MeshRender"))
            {
                if (ImGui::MenuItem(u8"추가"))
                {
                    if (nullptr == m_targetGO->GetComponent(COMPONENT_TYPE::MESHRENDER))
                        m_targetGO->AddComponent(new CMeshRender);
                }

                if (ImGui::MenuItem(u8"삭제"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("(RC)ParticleSystem"))
            {
                if (ImGui::MenuItem(u8"추가"))
                {
                    if (nullptr == m_targetGO->GetComponent(COMPONENT_TYPE::PARTICLESYSTEM))
                        m_targetGO->AddComponent(new CParticleSystem);
                }

                if (ImGui::MenuItem(u8"삭제"))
                {

                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("(RC)TileMap"))
            {
                if (ImGui::MenuItem(u8"추가"))
                {
                    if (nullptr == m_targetGO->GetComponent(COMPONENT_TYPE::TILEMAP))
                        m_targetGO->AddComponent(new CTileMap);
                }

                if (ImGui::MenuItem(u8"삭제"))
                {

                }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Script", ""))
        {
            vector<wstring> vecScriptName;
            CScriptMgr::GetScriptInfo(vecScriptName);

            for (size_t i = 0; i < vecScriptName.size(); ++i)
            {
                if (ImGui::BeginMenu(ToString(vecScriptName[i]).c_str()))
                {
                    Inspector* inspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");

                    if (ImGui::MenuItem(u8"추가"))
                    {
                        if (nullptr != inspector->GetTargetObject())
                        {
                            inspector->GetTargetObject()->AddComponent(CScriptMgr::GetScript(vecScriptName[i]));
                        }
                    }

                    if (ImGui::MenuItem(u8"삭제"))
                    {
                        if (nullptr != inspector->GetTargetObject())
                        {
                            inspector->GetTargetObject()->deleteScript(vecScriptName[i]);
                        }
                    }

                    ImGui::EndMenu(); // 스크립트 각각의 Begin
                }
            }

            ImGui::EndMenu();
        }

        ImGui::EndMenu();
    }
}

void MenuUI::Asset()
{
    if (ImGui::BeginMenu("Asset"))
    {
        if (ImGui::MenuItem("Create Empty Material"))
        {
            wchar_t szPath[255] = {};            
            wstring FilePath = CPathMgr::GetContentPath();
            
            int num = 0;
            while (true)
            {                
                swprintf_s(szPath, L"Material//New Material_%d.mtrl", num);
                if (!exists(FilePath + szPath))
                    break;
                ++num;
            }

            CMaterial* pMtrl = new CMaterial;
            pMtrl->SetName(szPath);
            pMtrl->Save(szPath);
            GamePlayStatic::AddAsset(pMtrl);
        }

        ImGui::EndMenu();
    }
}
