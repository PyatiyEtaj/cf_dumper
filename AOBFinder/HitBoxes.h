#pragma once
#include "HelpfulFuncs.h"

class HitBoxes
{
private:
	DWORD _cshell;
	DWORD GetModelById();
	DWORD GetPatch();
	DWORD GetModelBackUp();

public:
	void GetOffsets(std::vector<int> &v, DWORD cshell);
};