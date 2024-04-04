#include "pch.h"
#include "CStateMgr.h"

#include "CHaikuDashState.h"
#include "CHaikuDieState.h"
#include "CHaikuIdleState.h"
#include "CHaikuJumpFallState.h"
#include "CHaikuJumpRiseState.h"
#include "CHaikuPlatformGeneralAttackState.h"
#include "CHaikuRepairState.h"
#include "CHaikuStartState.h"
#include "CIdleState.h"
#include "CTraceState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CHaikuDashState");
	_vec.push_back(L"CHaikuDieState");
	_vec.push_back(L"CHaikuIdleState");
	_vec.push_back(L"CHaikuJumpFallState");
	_vec.push_back(L"CHaikuJumpRiseState");
	_vec.push_back(L"CHaikuPlatformGeneralAttackState");
	_vec.push_back(L"CHaikuRepairState");
	_vec.push_back(L"CHaikuStartState");
	_vec.push_back(L"CIdleState");
	_vec.push_back(L"CTraceState");
}

CState* CStateMgr::GetState(const wstring& _strStateName)
{
	if (L"CHaikuDashState" == _strStateName)
		return new CHaikuDashState;
	if (L"CHaikuDieState" == _strStateName)
		return new CHaikuDieState;
	if (L"CHaikuIdleState" == _strStateName)
		return new CHaikuIdleState;
	if (L"CHaikuJumpFallState" == _strStateName)
		return new CHaikuJumpFallState;
	if (L"CHaikuJumpRiseState" == _strStateName)
		return new CHaikuJumpRiseState;
	if (L"CHaikuPlatformGeneralAttackState" == _strStateName)
		return new CHaikuPlatformGeneralAttackState;
	if (L"CHaikuRepairState" == _strStateName)
		return new CHaikuRepairState;
	if (L"CHaikuStartState" == _strStateName)
		return new CHaikuStartState;
	if (L"CIdleState" == _strStateName)
		return new CIdleState;
	if (L"CTraceState" == _strStateName)
		return new CTraceState;
	return nullptr;
}

CState* CStateMgr::GetState(UINT _iStateType)
{
	switch (_iStateType)
	{
	case (UINT)STATE_TYPE::HAIKUDASHSTATE:
		return new CHaikuDashState;
		break;
	case (UINT)STATE_TYPE::HAIKUDIESTATE:
		return new CHaikuDieState;
		break;
	case (UINT)STATE_TYPE::HAIKUIDLESTATE:
		return new CHaikuIdleState;
		break;
	case (UINT)STATE_TYPE::HAIKUJUMPFALLSTATE:
		return new CHaikuJumpFallState;
		break;
	case (UINT)STATE_TYPE::HAIKUJUMPRISESTATE:
		return new CHaikuJumpRiseState;
		break;
	case (UINT)STATE_TYPE::HAIKUPLATFORMGENERALATTACKSTATE:
		return new CHaikuPlatformGeneralAttackState;
		break;
	case (UINT)STATE_TYPE::HAIKUREPAIRSTATE:
		return new CHaikuRepairState;
		break;
	case (UINT)STATE_TYPE::HAIKUSTARTSTATE:
		return new CHaikuStartState;
		break;
	case (UINT)STATE_TYPE::IDLESTATE:
		return new CIdleState;
		break;
	case (UINT)STATE_TYPE::TRACESTATE:
		return new CTraceState;
		break;
	}
	return nullptr;
}

const wchar_t * CStateMgr::GetStateName(CState * _pState)
{
	switch ((STATE_TYPE)_pState->GetStateType())
	{
	case STATE_TYPE::HAIKUDASHSTATE:
		return L"CHaikuDashState";
		break;

	case STATE_TYPE::HAIKUDIESTATE:
		return L"CHaikuDieState";
		break;

	case STATE_TYPE::HAIKUIDLESTATE:
		return L"CHaikuIdleState";
		break;

	case STATE_TYPE::HAIKUJUMPFALLSTATE:
		return L"CHaikuJumpFallState";
		break;

	case STATE_TYPE::HAIKUJUMPRISESTATE:
		return L"CHaikuJumpRiseState";
		break;

	case STATE_TYPE::HAIKUPLATFORMGENERALATTACKSTATE:
		return L"CHaikuPlatformGeneralAttackState";
		break;

	case STATE_TYPE::HAIKUREPAIRSTATE:
		return L"CHaikuRepairState";
		break;

	case STATE_TYPE::HAIKUSTARTSTATE:
		return L"CHaikuStartState";
		break;

	case STATE_TYPE::IDLESTATE:
		return L"CIdleState";
		break;

	case STATE_TYPE::TRACESTATE:
		return L"CTraceState";
		break;

	}
	return nullptr;
}