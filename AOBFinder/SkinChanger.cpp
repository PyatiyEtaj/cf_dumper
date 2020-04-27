#include "SkinChanger.h"

DWORD SkinChanger::GetWpnById()
{
	PBYTE res = FindPatternInModule(
		CrtVec("\x55\x8B\xEC\x66\x8B\x4D\x08\x66\x83\xF9\xFF", 11),
		"CShell.dll"
	);

	return (DWORD)res - _cshell;
}

DWORD SkinChanger::Get1()
{
	PBYTE res = FindPatternInModule(
		CrtVec("\xE8\x00\x00\x00\x00\x83\xC4\x04\x50\xE8\x00\x00\x00\x00\x8B\xF0\x83\xC4\x04", 19),
		"CShell.dll"
	);

	return (DWORD)res - _cshell;
}

DWORD SkinChanger::Get2()
{
	PBYTE res = FindPatternInModule(
		CrtVec("\xE8\x00\x00\x00\x00\x8B\xF8\x83\xC4\x04\x85\xFF\x0F\x84\x00\x00\x00\x00\x68\xA5\x00\x00\x00\x8D\x85\x8A\xFE\xFF\xFF", 29),
		"CShell.dll"
	);

	return (DWORD)res - _cshell;
}

DWORD SkinChanger::Get3()
{
	PBYTE res = FindPatternInModule(
		CrtVec("\xE8\x00\x00\x00\x00\x8B\xF0\x83\xC4\x04\x85\xF6\x0F\x84\x47\x02\x00\x00\xF3\x0F\x10\x86\x2C\x11", 24),
		"CShell.dll"
	);

	return (DWORD)res - _cshell;
}

DWORD SkinChanger::Get4()
{
	PBYTE res = FindPatternInModule(
		CrtVec("\x6A\x01\x56\x6A\x00\xFF\x90\x50\x01\x00\x00\x83\x7D\xEC\x10\x8D", 16),
		"CShell.dll"
	) - 0x5F;

	return (DWORD)res - _cshell;
}

void SkinChanger::GetOffsets(std::vector<int> &v, DWORD cshell)
{
	_cshell = (DWORD)GetModuleHandleA("CShell.dll");
	DWORD tmp = Get1();
	v.push_back(GetWpnById());
	v.push_back(tmp);
	v.push_back(tmp - 0x12);
	v.push_back(Get2());
	v.push_back(Get3());
	v.push_back(Get4());
}

/*std::string SkinChanger::GetOffsets(DWORD cshell)
{
	_cshell = (DWORD)GetModuleHandleA("CShell.dll");
	DWORD tmp = Get1();
	std::string result =
		std::to_string(GetWpnById()) + "\n" +
		std::to_string(tmp) + "\n" +
		std::to_string(tmp - 0x12) + "\n" +
		std::to_string(Get2()) + "\n" +
		std::to_string(Get3()) + "\n" +
		std::to_string(Get4()) + "\n";

	return result;
}*/
