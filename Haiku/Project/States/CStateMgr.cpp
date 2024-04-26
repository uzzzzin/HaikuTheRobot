#include "pch.h"
#include "CStateMgr.h"

#include "CHaikuDashState.h"
#include "CHaikuDieState.h"
#include "CHaikuIdleState.h"
#include "CHaikuIntroState.h"
#include "CHaikuJumpFallGeneralAttackState.h"
#include "CHaikuJumpFallState.h"
#include "CHaikuJumpRiseDownAttackState.h"
#include "CHaikuJumpRiseGeneralAttackState.h"
#include "CHaikuJumpRiseState.h"
#include "CHaikuJumpRiseUpAttackState.h"
#include "CHaikuPlatformGeneralAttackState.h"
#include "CHaikuRepairState.h"
#include "CHaikuStartState.h"
#include "CHaikuWalkState.h"
#include "CIdleState.h"
#include "CNuttyAttackedState.h"
#include "CNuttyDetectState.h"
#include "CNuttyIdleState.h"
#include "CNuttyTraceState.h"
#include "CSGMNullState.h"
#include "CSGMStartState.h"
#include "CSGMUpOnTopState.h"
#include "CSGMUpToMiddleState.h"
#include "CSGMYumOnMiddleState.h"
#include "CTireDieState.h"
#include "CTireIdleState.h"
#include "CTraceState.h"

void CStateMgr::GetStateInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CHaikuDashState");
	_vec.push_back(L"CHaikuDieState");
	_vec.push_back(L"CHaikuIdleState");
	_vec.push_back(L"CHaikuIntroState");
	_vec.push_back(L"CHaikuJumpFallGeneralAttackState");
	_vec.push_back(L"CHaikuJumpFallState");
	_vec.push_back(L"CHaikuJumpRiseDownAttackState");
	_vec.push_back(L"CHaikuJumpRiseGeneralAttackState");
	_vec.push_back(L"CHaikuJumpRiseState");
	_vec.push_back(L"CHaikuJumpRiseUpAttackState");
	_vec.push_back(L"CHaikuPlatformGeneralAttackState");
	_vec.push_back(L"CHaikuRepairState");
	_vec.push_back(L"CHaikuStartState");
	_vec.push_back(L"CHaikuWalkState");
	_vec.push_back(L"CIdleState");
	_vec.push_back(L"CNuttyAttackedState");
	_vec.push_back(L"CNuttyDetectState");
	_vec.push_back(L"CNuttyIdleState");
	_vec.push_back(L"CNuttyTraceState");
	_vec.push_back(L"CSGMNullState");
	_vec.push_back(L"CSGMStartState");
	_vec.push_back(L"CSGMUpOnTopState");
	_vec.push_back(L"CSGMUpToMiddleState");
	_vec.push_back(L"CSGMYumOnMiddleState");
	_vec.push_back(L"CTireDieState");
	_vec.push_back(L"CTireIdleState");
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
	if (L"CHaikuIntroState" == _strStateName)
		return new CHaikuIntroState;
	if (L"CHaikuJumpFallGeneralAttackState" == _strStateName)
		return new CHaikuJumpFallGeneralAttackState;
	if (L"CHaikuJumpFallState" == _strStateName)
		return new CHaikuJumpFallState;
	if (L"CHaikuJumpRiseDownAttackState" == _strStateName)
		return new CHaikuJumpRiseDownAttackState;
	if (L"CHaikuJumpRiseGeneralAttackState" == _strStateName)
		return new CHaikuJumpRiseGeneralAttackState;
	if (L"CHaikuJumpRiseState" == _strStateName)
		return new CHaikuJumpRiseState;
	if (L"CHaikuJumpRiseUpAttackState" == _strStateName)
		return new CHaikuJumpRiseUpAttackState;
	if (L"CHaikuPlatformGeneralAttackState" == _strStateName)
		return new CHaikuPlatformGeneralAttackState;
	if (L"CHaikuRepairState" == _strStateName)
		return new CHaikuRepairState;
	if (L"CHaikuStartState" == _strStateName)
		return new CHaikuStartState;
	if (L"CHaikuWalkState" == _strStateName)
		return new CHaikuWalkState;
	if (L"CIdleState" == _strStateName)
		return new CIdleState;
	if (L"CNuttyAttackedState" == _strStateName)
		return new CNuttyAttackedState;
	if (L"CNuttyDetectState" == _strStateName)
		return new CNuttyDetectState;
	if (L"CNuttyIdleState" == _strStateName)
		return new CNuttyIdleState;
	if (L"CNuttyTraceState" == _strStateName)
		return new CNuttyTraceState;
	if (L"CSGMNullState" == _strStateName)
		return new CSGMNullState;
	if (L"CSGMStartState" == _strStateName)
		return new CSGMStartState;
	if (L"CSGMUpOnTopState" == _strStateName)
		return new CSGMUpOnTopState;
	if (L"CSGMUpToMiddleState" == _strStateName)
		return new CSGMUpToMiddleState;
	if (L"CSGMYumOnMiddleState" == _strStateName)
		return new CSGMYumOnMiddleState;
	if (L"CTireDieState" == _strStateName)
		return new CTireDieState;
	if (L"CTireIdleState" == _strStateName)
		return new CTireIdleState;
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
	case (UINT)STATE_TYPE::HAIKUINTROSTATE:
		return new CHaikuIntroState;
		break;
	case (UINT)STATE_TYPE::HAIKUJUMPFALLGENERALATTACKSTATE:
		return new CHaikuJumpFallGeneralAttackState;
		break;
	case (UINT)STATE_TYPE::HAIKUJUMPFALLSTATE:
		return new CHaikuJumpFallState;
		break;
	case (UINT)STATE_TYPE::HAIKUJUMPRISEDOWNATTACKSTATE:
		return new CHaikuJumpRiseDownAttackState;
		break;
	case (UINT)STATE_TYPE::HAIKUJUMPRISEGENERALATTACKSTATE:
		return new CHaikuJumpRiseGeneralAttackState;
		break;
	case (UINT)STATE_TYPE::HAIKUJUMPRISESTATE:
		return new CHaikuJumpRiseState;
		break;
	case (UINT)STATE_TYPE::HAIKUJUMPRISEUPATTACKSTATE:
		return new CHaikuJumpRiseUpAttackState;
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
	case (UINT)STATE_TYPE::HAIKUWALKSTATE:
		return new CHaikuWalkState;
		break;
	case (UINT)STATE_TYPE::IDLESTATE:
		return new CIdleState;
		break;
	case (UINT)STATE_TYPE::NUTTYATTACKEDSTATE:
		return new CNuttyAttackedState;
		break;
	case (UINT)STATE_TYPE::NUTTYDETECTSTATE:
		return new CNuttyDetectState;
		break;
	case (UINT)STATE_TYPE::NUTTYIDLESTATE:
		return new CNuttyIdleState;
		break;
	case (UINT)STATE_TYPE::NUTTYTRACESTATE:
		return new CNuttyTraceState;
		break;
	case (UINT)STATE_TYPE::SGMNULLSTATE:
		return new CSGMNullState;
		break;
	case (UINT)STATE_TYPE::SGMSTARTSTATE:
		return new CSGMStartState;
		break;
	case (UINT)STATE_TYPE::SGMUPONTOPSTATE:
		return new CSGMUpOnTopState;
		break;
	case (UINT)STATE_TYPE::SGMUPTOMIDDLESTATE:
		return new CSGMUpToMiddleState;
		break;
	case (UINT)STATE_TYPE::SGMYUMONMIDDLESTATE:
		return new CSGMYumOnMiddleState;
		break;
	case (UINT)STATE_TYPE::TIREDIESTATE:
		return new CTireDieState;
		break;
	case (UINT)STATE_TYPE::TIREIDLESTATE:
		return new CTireIdleState;
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

	case STATE_TYPE::HAIKUINTROSTATE:
		return L"CHaikuIntroState";
		break;

	case STATE_TYPE::HAIKUJUMPFALLGENERALATTACKSTATE:
		return L"CHaikuJumpFallGeneralAttackState";
		break;

	case STATE_TYPE::HAIKUJUMPFALLSTATE:
		return L"CHaikuJumpFallState";
		break;

	case STATE_TYPE::HAIKUJUMPRISEDOWNATTACKSTATE:
		return L"CHaikuJumpRiseDownAttackState";
		break;

	case STATE_TYPE::HAIKUJUMPRISEGENERALATTACKSTATE:
		return L"CHaikuJumpRiseGeneralAttackState";
		break;

	case STATE_TYPE::HAIKUJUMPRISESTATE:
		return L"CHaikuJumpRiseState";
		break;

	case STATE_TYPE::HAIKUJUMPRISEUPATTACKSTATE:
		return L"CHaikuJumpRiseUpAttackState";
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

	case STATE_TYPE::HAIKUWALKSTATE:
		return L"CHaikuWalkState";
		break;

	case STATE_TYPE::IDLESTATE:
		return L"CIdleState";
		break;

	case STATE_TYPE::NUTTYATTACKEDSTATE:
		return L"CNuttyAttackedState";
		break;

	case STATE_TYPE::NUTTYDETECTSTATE:
		return L"CNuttyDetectState";
		break;

	case STATE_TYPE::NUTTYIDLESTATE:
		return L"CNuttyIdleState";
		break;

	case STATE_TYPE::NUTTYTRACESTATE:
		return L"CNuttyTraceState";
		break;

	case STATE_TYPE::SGMNULLSTATE:
		return L"CSGMNullState";
		break;

	case STATE_TYPE::SGMSTARTSTATE:
		return L"CSGMStartState";
		break;

	case STATE_TYPE::SGMUPONTOPSTATE:
		return L"CSGMUpOnTopState";
		break;

	case STATE_TYPE::SGMUPTOMIDDLESTATE:
		return L"CSGMUpToMiddleState";
		break;

	case STATE_TYPE::SGMYUMONMIDDLESTATE:
		return L"CSGMYumOnMiddleState";
		break;

	case STATE_TYPE::TIREDIESTATE:
		return L"CTireDieState";
		break;

	case STATE_TYPE::TIREIDLESTATE:
		return L"CTireIdleState";
		break;

	case STATE_TYPE::TRACESTATE:
		return L"CTraceState";
		break;

	}
	return nullptr;
}