#pragma once

class CEngine 
	: public CSingleton<CEngine>
{
	SINGLE(CEngine);
private:
	HWND		m_hMainWnd;		// ���� ������ �ڵ�
	Vec2		m_vResolution;	// �ػ� ����

public:
	HWND GetMainWind() { return m_hMainWnd; }
	Vec2 GetResolution() { return m_vResolution; }

private:
	void DebugFunctionCheck();

public:
	int init(HWND _hWnd, Vec2 _vResolution);
	void progress();
};

