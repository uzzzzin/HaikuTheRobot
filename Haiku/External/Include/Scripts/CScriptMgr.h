#pragma once

#include <vector>
#include <string>

enum SCRIPT_TYPE
{
	BACKGROUNDSCRIPT,
	CAMEVENTSCRIPT,
	CHANGEROOMSCRIPT,
	CTRLSCRIPT,
	HAIKUSCRIPT,
	HAIKUSWORDSCRIPT,
	MISSILESCRIPT,
	MONSTERSCRIPT,
	NUTTYSCRIPT,
	PLATFORMSCRIPT,
	PLAYERSCRIPT,
	ROOMMGRSCRIPT,
	SCREWSCRIPT,
	TIREDTIRESCRIPT,
	TRACECAMERASCRIPT,
	END,
};

using namespace std;

class CScript;

class CScriptMgr
{
public:
	static void GetScriptInfo(vector<wstring>& _vec);
	static CScript * GetScript(const wstring& _strScriptName);
	static CScript * GetScript(UINT _iScriptType);
	static const wchar_t * GetScriptName(CScript * _pScript);
};
