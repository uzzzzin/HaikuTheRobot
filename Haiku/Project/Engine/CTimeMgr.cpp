#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CFontMgr.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_Time(0.f)
	, m_bLock(true)
	, m_szText{}
{	

}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	// �ʴ� ��
	QueryPerformanceFrequency(&m_Frequency);

	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_CurCount);

	m_EngineDeltaTime = m_DeltaTime = double(m_CurCount.QuadPart - m_PrevCount.QuadPart) / double(m_Frequency.QuadPart);

	if (m_bLock)
	{
		m_DeltaTime = 0.f;
	}

	m_PrevCount = m_CurCount;

	// DT ����
	if ((1.f / 60.f) < m_DeltaTime)
		m_DeltaTime = (1. / 60.);

	// �ð� ���� ==> 1�ʸ��� if ���� ����
	m_Time += m_EngineDeltaTime;
	m_szText[50] = {};
	if (1.f <= m_Time)
	{		
		swprintf_s(m_szText, 50, L"DeltaTime : %f, FPS : %d", m_DeltaTime, m_iCall);
		m_iCall = 0;
		m_Time = 0.f;
	}

	++m_iCall;	

	g_global.g_dt = (float)m_DeltaTime;
	g_global.g_time += (float)m_DeltaTime;
}

void CTimeMgr::render()
{
	// ��Ʈ ���
	//CFontMgr::GetInst()->DrawFont(m_szText, 10.f, 30.f, 16, FONT_RGBA(255, 30, 30, 255));

	// ��Ʈ ���
	CFontMgr::GetInst()->DrawFont(m_szText, 300.f, 40.f, 16, FONT_RGBA(255, 30, 30, 255));
}