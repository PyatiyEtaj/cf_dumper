#pragma once
#include "HelpfulFuncs.h"

/*std::string GetDIPEngineOffs(DWORD crossfire)
{
	PBYTE ptr = __findPattern("\x8B\x07\xFF\x75\x18", 5, "crossfire.exe");

	return std::to_string((DWORD)((DWORD)ptr - crossfire)) + "\n";
}*/
void GetDIPEngineOffs(std::vector<int>& v, DWORD crossfire)
{
	PBYTE ptr = __findPattern("\x8B\x07\xFF\x75\x18", 5, "crossfire.exe");

	v.push_back((DWORD)((DWORD)ptr - crossfire));
}
