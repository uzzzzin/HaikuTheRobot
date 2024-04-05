#pragma once

#include <vector>
#include <string>

enum STATE_TYPE
{
	HAIKUDASHSTATE,
	HAIKUDIESTATE,
	HAIKUIDLESTATE,
	HAIKUJUMPFALLSTATE,
	HAIKUJUMPRISEDOWNATTACKSTATE,
	HAIKUJUMPRISEGENERALATTACKSTATE,
	HAIKUJUMPRISESTATE,
	HAIKUJUMPRISEUPATTACKSTATE,
	HAIKUPLATFORMGENERALATTACKSTATE,
	HAIKUREPAIRSTATE,
	HAIKUSTARTSTATE,
	HAIKUWALKSTATE,
	IDLESTATE,
	TRACESTATE,
	STATE_END,
};

using namespace std;

class CState;

class CStateMgr
{
public:
	static void GetStateInfo(vector<wstring>& _vec);
	static CState * GetState(const wstring& _strStateName);
	static CState * GetState(UINT _iStateType);
	static const wchar_t * GetStateName(CState * _pState);
};
