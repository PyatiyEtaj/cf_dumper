#pragma once
#include "HelpfulFuncs.h"

class SkinChanger
{
private:
	DWORD _cshell;
	DWORD GetWpnById();
	DWORD Get1();
	DWORD Get2(); 
	DWORD Get4();
	DWORD Get3();

public:
	void GetOffsets(std::vector<int>& v, DWORD cshell);
};
