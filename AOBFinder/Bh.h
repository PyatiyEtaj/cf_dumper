#pragma once
#include "HelpfulFuncs.h"

/*std::string GetBhOffs(DWORD cshell)
{
	void* ptr = __findPattern("\x0F\xB6\x05\x00\x00\x00\x00\x8B\xCF\x50\x8D", 11) + 0x3;
	
	return std::to_string((DWORD)((DWORD)ptr - cshell)) + "\n";
}*/

void GetBhOffs(std::vector<int>& v, DWORD cshell)
{
	void* ptr = __findPattern("\x0F\xB6\x05\x00\x00\x00\x00\x8B\xCF\x50\x8D", 11) + 0x3;

	v.push_back((DWORD)((DWORD)ptr - cshell));
}