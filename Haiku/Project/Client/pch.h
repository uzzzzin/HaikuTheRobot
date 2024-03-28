#pragma once



#define IMGUI_DEFINE_MATH_OPERATORS

#include <Engine/global.h>

#include <string.h>
using std::string;
using std::wstring;

// State lib
#ifdef _DEBUG
#pragma comment(lib, "States\\States_d.lib")
#else
#pragma comment(lib, "States\\States.lib")
#endif