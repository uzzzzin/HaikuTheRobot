#include "pch.h"
#include "CScriptMgr.h"

#include "CBackgroundScript.h"
#include "CBoss1RoomScript.h"
#include "CCamEventScript.h"
#include "CChangeRoomScript.h"
#include "CCtrlScript.h"
#include "CHaikuScript.h"
#include "CHaikuSwordScript.h"
#include "CIntroParticleScript.h"
#include "CMainCameraScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CNuttyScript.h"
#include "CPlatformScript.h"
#include "CPlayerScript.h"
#include "CRoomMgrScript.h"
#include "CScrewScript.h"
#include "CSwingingGarbageMagnetScript.h"
#include "CTiredTireScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CBoss1RoomScript");
	_vec.push_back(L"CCamEventScript");
	_vec.push_back(L"CChangeRoomScript");
	_vec.push_back(L"CCtrlScript");
	_vec.push_back(L"CHaikuScript");
	_vec.push_back(L"CHaikuSwordScript");
	_vec.push_back(L"CIntroParticleScript");
	_vec.push_back(L"CMainCameraScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CNuttyScript");
	_vec.push_back(L"CPlatformScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CRoomMgrScript");
	_vec.push_back(L"CScrewScript");
	_vec.push_back(L"CSwingingGarbageMagnetScript");
	_vec.push_back(L"CTiredTireScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CBoss1RoomScript" == _strScriptName)
		return new CBoss1RoomScript;
	if (L"CCamEventScript" == _strScriptName)
		return new CCamEventScript;
	if (L"CChangeRoomScript" == _strScriptName)
		return new CChangeRoomScript;
	if (L"CCtrlScript" == _strScriptName)
		return new CCtrlScript;
	if (L"CHaikuScript" == _strScriptName)
		return new CHaikuScript;
	if (L"CHaikuSwordScript" == _strScriptName)
		return new CHaikuSwordScript;
	if (L"CIntroParticleScript" == _strScriptName)
		return new CIntroParticleScript;
	if (L"CMainCameraScript" == _strScriptName)
		return new CMainCameraScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CNuttyScript" == _strScriptName)
		return new CNuttyScript;
	if (L"CPlatformScript" == _strScriptName)
		return new CPlatformScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CRoomMgrScript" == _strScriptName)
		return new CRoomMgrScript;
	if (L"CScrewScript" == _strScriptName)
		return new CScrewScript;
	if (L"CSwingingGarbageMagnetScript" == _strScriptName)
		return new CSwingingGarbageMagnetScript;
	if (L"CTiredTireScript" == _strScriptName)
		return new CTiredTireScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSS1ROOMSCRIPT:
		return new CBoss1RoomScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMEVENTSCRIPT:
		return new CCamEventScript;
		break;
	case (UINT)SCRIPT_TYPE::CHANGEROOMSCRIPT:
		return new CChangeRoomScript;
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
	case (UINT)SCRIPT_TYPE::INTROPARTICLESCRIPT:
		return new CIntroParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINCAMERASCRIPT:
		return new CMainCameraScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::NUTTYSCRIPT:
		return new CNuttyScript;
		break;
	case (UINT)SCRIPT_TYPE::PLATFORMSCRIPT:
		return new CPlatformScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::ROOMMGRSCRIPT:
		return new CRoomMgrScript;
		break;
	case (UINT)SCRIPT_TYPE::SCREWSCRIPT:
		return new CScrewScript;
		break;
	case (UINT)SCRIPT_TYPE::SWINGINGGARBAGEMAGNETSCRIPT:
		return new CSwingingGarbageMagnetScript;
		break;
	case (UINT)SCRIPT_TYPE::TIREDTIRESCRIPT:
		return new CTiredTireScript;
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

	case SCRIPT_TYPE::BOSS1ROOMSCRIPT:
		return L"CBoss1RoomScript";
		break;

	case SCRIPT_TYPE::CAMEVENTSCRIPT:
		return L"CCamEventScript";
		break;

	case SCRIPT_TYPE::CHANGEROOMSCRIPT:
		return L"CChangeRoomScript";
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

	case SCRIPT_TYPE::INTROPARTICLESCRIPT:
		return L"CIntroParticleScript";
		break;

	case SCRIPT_TYPE::MAINCAMERASCRIPT:
		return L"CMainCameraScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::NUTTYSCRIPT:
		return L"CNuttyScript";
		break;

	case SCRIPT_TYPE::PLATFORMSCRIPT:
		return L"CPlatformScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::ROOMMGRSCRIPT:
		return L"CRoomMgrScript";
		break;

	case SCRIPT_TYPE::SCREWSCRIPT:
		return L"CScrewScript";
		break;

	case SCRIPT_TYPE::SWINGINGGARBAGEMAGNETSCRIPT:
		return L"CSwingingGarbageMagnetScript";
		break;

	case SCRIPT_TYPE::TIREDTIRESCRIPT:
		return L"CTiredTireScript";
		break;

	}
	return nullptr;
}