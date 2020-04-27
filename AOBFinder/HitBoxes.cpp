#include "HitBoxes.h"

DWORD HitBoxes::GetModelById()
{
	PBYTE res = FindPatternInModule(
		CrtVec("\x69\xC1\x9C\x00\x00\x00\x03\x05\x00\x00\x00\x00\x5D\xC3\x33\xC0\x5D\xC3", 18),
		"CShell.dll"
	) - 0x1C;

	return (DWORD)res - _cshell;
}

DWORD HitBoxes::GetPatch()
{
	PBYTE res = FindPatternInModule(
		CrtVec("\xE8\x00\x00\x00\x00\x83\xC4\x04\x85\xC0\x74\x18\x68\x9C\x00\x00\x00\x50\x6A\x00\xE8", 21),
		"CShell.dll"
	);

	return (DWORD)res - _cshell;
}

DWORD HitBoxes::GetModelBackUp()
{
	PBYTE res = FindPatternInModule(CrtVec("\x8B\x0D\x00\x00\x00\x00\x81\xFE", 8), "CShell.dll") + 0x2;

	return (DWORD)res - _cshell;
}

void HitBoxes::GetOffsets(std::vector<int>& v, DWORD cshell)
{
	_cshell = cshell;
	v.push_back(GetModelBackUp());
	v.push_back(GetModelById());
	v.push_back(GetPatch());
}

/*void HitBoxes::GetOffsets(std::vector<int>& v, DWORD cshell)
{
	_cshell = cshell;
	std::string result =
		std::to_string(GetModelBackUp()) + "\n" +
		std::to_string(GetModelById()) + "\n" +
		std::to_string(GetPatch()) + "\n";

	return result;
}*/
