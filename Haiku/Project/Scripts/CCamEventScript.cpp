#include "pch.h"
#include "CCamEventScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CCamEventScript::CCamEventScript()
	: CScript(CAMEVENTSCRIPT)
	, m_EventExecute(false)
	, m_CurEventAccTime (0)
{
}

CCamEventScript::~CCamEventScript()
{
}

void CCamEventScript::begin()
{
	m_Directional_Light = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Directional Light");

	CGameObject* MainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	MainCam->GetScript<CCamEventScript>()->FadeOut(1.f);
}

void CCamEventScript::tick()
{
	// 이벤트 있으면 동작하세용

	if (m_EventList.empty())
		return;

	FCamEvent &CurEvent = m_EventList.front();

	if (CurEvent.Type == CAM_EFFECT::FADE_IN)
		FadeIn_Imp(CurEvent);

	if (CurEvent.Type == CAM_EFFECT::FADE_OUT)
		FadeOut_Imp(CurEvent);

	if (CurEvent.Type == CAM_EFFECT::SHAKE)
		Shake_Imp(CurEvent);
}

void CCamEventScript::FadeIn(float _time)
{
	FCamEvent event = {};
	event.Type = CAM_EFFECT::FADE_IN;
	event.Duration = _time;
	m_EventList.push_back(event);

}

void CCamEventScript::FadeOut(float _time)
{
	FCamEvent event = {};
	event.Type = CAM_EFFECT::FADE_OUT;
	event.Duration = _time;
	m_EventList.push_back(event);
}

void CCamEventScript::Shake(float _time, int _size)
{
	FCamEvent evnt = {};
	evnt.Type = CAM_EFFECT::SHAKE;
	evnt.Duration = _time;
	evnt.ShakingSize = _size;
	m_EventList.push_back(evnt);
}

void CCamEventScript::FadeIn_Imp(FCamEvent _event)
{
	if (m_EventExecute == false) // 이벤트가 처음 수행되어질 때
	{
		m_Origin_Ambient = m_Directional_Light->Light2D()->GetAmbient();
		m_Directional_Light->Light2D()->SetAmbient(Vec3(0,0,0));
		m_EventExecute = true;
	}

	m_CurEventAccTime += DT;

	if (_event.Duration > m_CurEventAccTime)
	{
		if (m_Directional_Light->Light2D()->GetAmbient() >= m_Origin_Ambient)
			return; // 초기 앰비언트보다 밝아진다면..

		else
		{
			float fRatio = m_CurEventAccTime / _event.Duration;
			float fValue = fRatio;
			m_Directional_Light->Light2D()->SetAmbient(Vec3(fValue, fValue, fValue));
		}
	}
	else
	{
		m_EventList.pop_front();
		m_EventExecute = false;
		m_CurEventAccTime = 0;
	}
}

void CCamEventScript::FadeOut_Imp(FCamEvent _event)
{
	if (m_EventExecute == false) // 이벤트가 처음 수행되어질 때
	{
		m_Origin_Ambient = m_Directional_Light->Light2D()->GetAmbient();
		m_EventExecute = true;
	}

	m_CurEventAccTime += DT;

	if (_event.Duration > m_CurEventAccTime)
	{

		float fRatio = m_CurEventAccTime / _event.Duration;
		float fValue = 1 - fRatio;
		m_Directional_Light->Light2D()->SetAmbient(Vec3(fValue, fValue, fValue));
	}
	else
	{
		m_EventList.pop_front();
		m_EventExecute = false;
		m_CurEventAccTime = 0;
	}
}

void CCamEventScript::Shake_Imp(FCamEvent _event)
{
	m_CurEventAccTime += DT;

	if (_event.Duration > m_CurEventAccTime)
	{


	}
	else
	{
		m_EventList.pop_front();
	}
}

void CCamEventScript::SaveToFile(FILE* _File)
{
}

void CCamEventScript::LoadFromFile(FILE* _File)
{
}