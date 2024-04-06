#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CCtrlScript.h"
#include "CHaikuScript.h"
#include "CHaikuSwordScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlatformScript.h"
#include "CPlayerScript.h"
#include "CTraceCameraScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CCtrlScript");
	_vec.push_back(L"CHaikuScript");
	_vec.push_back(L"CHaikuSwordScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlatformScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CTraceCameraScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CCtrlScript" == _strScriptName)
		return new CCtrlScript;
	if (L"CHaikuScript" == _strScriptName)
		return new CHaikuScript;
	if (L"CHaikuSwordScript" == _strScriptName)
		return new CHaikuSwordScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlatformScript" == _strScriptName)
		return new CPlatformScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CTraceCameraScript" == _strScriptName)
		return new CTraceCameraScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::CTRLSCRIPT:
		return new CCtrlScript;
		break;
	case (UINT)SCRIPT_TYPE::HAIKUSCRIPT:
		return new CHaikuScript;
		break;
	case (UINT)SCRIPT_TYPE::HAIKUSWORDSCRIPT:
		return new CHaikuSwordScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLATFORMSCRIPT:
		return new CPlatformScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::TRACECAMERASCRIPT:
		return new CTraceCameraScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return L"CBackgroundScript";
		break;

	case SCRIPT_TYPE::CTRLSCRIPT:
		return L"CCtrlScript";
		break;

	case SCRIPT_TYPE::HAIKUSCRIPT:
		return L"CHaikuScript";
		break;

	case SCRIPT_TYPE::HAIKUSWORDSCRIPT:
		return L"CHaikuSwordScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLATFORMSCRIPT:
		return L"CPlatformScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::TRACECAMERASCRIPT:
		return L"CTraceCameraScript";
		break;

	}
	return nullptr;
}