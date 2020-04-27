#pragma once
#include "HelpfulFuncs.h"

/*std::string GetEspOffs(std::vector<int>& v, DWORD cshell)
{
	PBYTE ptr = __findPattern("\x55\x8B\xEC\x51\xA1\x00\x00\x00\x00\x53\x8B\x5D\x08\x56", 14);

	return std::to_string((DWORD)((DWORD)ptr - cshell)) + "\n";
}*/

void GetEspOffs(std::vector<int>& v, DWORD cshell)
{
	PBYTE ptr = __findPattern("\x55\x8B\xEC\x51\xA1\x00\x00\x00\x00\x53\x8B\x5D\x08\x56", 14);

	v.push_back((DWORD)((DWORD)ptr - cshell));
}