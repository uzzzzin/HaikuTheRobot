#include "pch.h"
#include "CImGuiMgr.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CGameObject.h>

#include <Engine/CPathMgr.h>

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "Inspector.h"
#include "Content.h"
#include "Outliner.h"
#include "MenuUI.h"
#include "ListUI.h"
#include "MtrlEditorUI.h"
#include "ParamUI.h"

#include <Engine/CDevice.h>
#include <Engine/CRenderMgr.h>
#include <Engine/CTaskMgr.h>

#include "EditorCamUI.h"
#include "ObjectController.h"

CImGuiMgr::CImGuiMgr()
    : m_bDemoUI(true)
    , m_hNotify(nullptr)
{

}

CImGuiMgr::~CImGuiMgr()
{
    // ImGui Clear       
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    // UI 
    Delete_Map(m_mapUI);

    // 디렉터리 변경 감시 종료
    FindCloseChangeNotification(m_hNotify);
}

void CImGuiMgr::init(HWND _hMainWnd, ComPtr<ID3D11Device> _Device
    , ComPtr<ID3D11DeviceContext> _Context)
{
    // ImGui 초기화
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;
    //io.ConfigViewportsNoDefaultParent = true;
    //io.ConfigDockingAlwaysTabBar = true;
    //io.ConfigDockingTransparentPayload = true;
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
    //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(_hMainWnd);
    ImGui_ImplDX11_Init(_Device.Get(), _Context.Get());

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

    
    // 한글 폰트 적용
    wstring path = CPathMgr::GetContentPath();
    path += L"fonts\\dulgi.ttf";
    string pa = ToString(path);
    io.Fonts->AddFontFromFileTTF(pa.c_str(), 18.0f, NULL, io.Fonts->GetGlyphRangesKorean());

    create_ui();

    // Content 폴더 감시
    wstring strContentPath = CPathMgr::GetContentPath();
    m_hNotify = FindFirstChangeNotification(strContentPath.c_str(), true
                                        , FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_DIR_NAME 
                                        | FILE_ACTION_ADDED | FILE_ACTION_REMOVED);
}

void CImGuiMgr::progress()
{
    tick();

    render();

    observe_content();
}

void CImGuiMgr::tick()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    if (CTaskMgr::GetInst()->GetChangeLevel())
    {
        LoadLayerName();
    }
    
    if (m_bDemoUI)
    {
        ImGui::ShowDemoWindow(&m_bDemoUI);
    }

    for (const auto& pair : m_mapUI)
    {
        pair.second->tick();
    }

    ParamUI::ResetID();
}

void CImGuiMgr::render()
{
    for (const auto& pair : m_mapUI)
    {
        pair.second->render();
    }

    render_copytex();

    // Rendering
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}


UI* CImGuiMgr::FindUI(const string& _strUIName)
{
    map<string, UI*>::iterator iter = m_mapUI.find(_strUIName);

    if (iter == m_mapUI.end())
        return nullptr;

    return iter->second;
}

void CImGuiMgr::AddUI(const string& _strKey, UI* _UI)
{
    UI* pUI = FindUI(_strKey);
    assert(!pUI);
    m_mapUI.insert(make_pair(_strKey, _UI));
}



void CImGuiMgr::create_ui()
{
    UI* pUI = nullptr;

    // Inspector
    pUI = new Inspector;
    AddUI(pUI->GetID(), pUI);

    // Content
    pUI = new Content;
    AddUI(pUI->GetID(), pUI);

    // Outliner
    pUI = new Outliner;
    AddUI(pUI->GetID(), pUI);

    // MenuUI
    pUI = new MenuUI;
    AddUI(pUI->GetID(), pUI);

    // List
    pUI = new ListUI;
    AddUI(pUI->GetID(), pUI);

    // Mtrl Inspector
    pUI = new MtrlEditorUI;
    AddUI(pUI->GetID(), pUI);

    // Editor Cam UI
    pUI = new EditorCamUI;
    AddUI(pUI->GetID(), pUI);
}

void CImGuiMgr::observe_content()
{
    // WaitForSingleObject 를 이용해서 알림이 있는지 확인,
    // 대기시간은 0로 설정해서 알림이 있던 없던 바로 반환
    if (WAIT_OBJECT_0 == WaitForSingleObject(m_hNotify, 0))
    {
        // 다시 알림 활성화
        FindNextChangeNotification(m_hNotify);

        // ContentUI 에 Reload 작업 수행
        Content* pContentUI = (Content*)FindUI("##Content");
        pContentUI->ReloadContent();
    }
}



void CImGuiMgr::render_copytex()
{
    ImGui::Begin("Viewport##GameWindow");


    Vec2 RenderResolution = CDevice::GetInst()->GetRenderResolution();
    ImVec2 RenderResol = { RenderResolution.x,RenderResolution.y };
    Ptr<CTexture> pCopyTex = CRenderMgr::GetInst()->GetRTCopyTex();

    // 현재 크기
    ImVec2 contentSize = ImGui::GetContentRegionAvail();

    Vec2 vResolution = CDevice::GetInst()->GetRenderResolution();
    ImVec2 Resolution = { vResolution.x,vResolution.y };

    ImVec2 LeftTopUv;
    LeftTopUv.x = ((vResolution.x - contentSize.x) / 2.f) / Resolution.x;
    LeftTopUv.y = ((vResolution.y - contentSize.y) / 2.f) / Resolution.y;

    ImVec2 RightBottom;
    RightBottom.x = 1.f - LeftTopUv.x;
    RightBottom.y = 1.f - LeftTopUv.y;

    // Image 위치 기록
    ImVec2 windowPos = ImGui::GetCursorScreenPos();
    ImVec2 windowSize = ImVec2(Resolution.x * (RightBottom.x - LeftTopUv.x), Resolution.y * (RightBottom.y - LeftTopUv.y));
    Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");

    pInspector->GetObjController()->SetStartPos(windowPos);
    pInspector->GetObjController()->SetViewportSize(windowSize);

    // Image 출력
    ImGui::Image((void*)pCopyTex->GetSRV().Get(), ImVec2(Resolution.x * (RightBottom.x - LeftTopUv.x), Resolution.y * (RightBottom.y - LeftTopUv.y)), LeftTopUv, RightBottom);

    // case: drop
   if (ImGui::IsMouseReleased(0) && ImGui::BeginDragDropTarget())
   {
      if (m_Prefab.Get())
      {
         GamePlayStatic::SpawnGameObject(m_Prefab->Instantiate(), 0);
      }

      ImGui::EndDragDropTarget();
   }

    ImGui::End();

}

void CImGuiMgr::LoadLayerName()
{
    m_LayerName.clear();

    CLevel* pLevel = CLevelMgr::GetInst()->GetCurrentLevel();

    for (int i = 0; i < LAYER_MAX; ++i)
    {
        wstring layerName = pLevel->GetLayer(i)->GetName();
        string strLayerName = string(layerName.begin(), layerName.end());
        if (strLayerName == "")
        {
            strLayerName = std::to_string(i);
        }

        m_LayerName.push_back("[" + std::to_string(i) + "]" + " " + strLayerName);
    }
}

void CImGuiMgr::DragPrefab(DWORD_PTR _pref)
{
    Ptr<CAsset> pAsset = (CAsset*)_pref;

    if (pAsset.Get() && pAsset->GetType() == ASSET_TYPE::PREFAB)
    {
        m_Prefab = (CPrefab*)pAsset.Get();
    }
}