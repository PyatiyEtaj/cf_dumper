#pragma once
#include "framework.h"

enum ModulesNameEnum {
	CShell = 0,
	Crossfire = 1
};

class sigfnd {
private:
	DWORD _modules[2];
	const char* _modulesname[2];
	std::ofstream f;

public:
	sigfnd()
	{
		_modules[0] = (DWORD)GetModuleHandleA("CShell.dll");
		_modules[1] = (DWORD)GetModuleHandleA("crossfire.exe");
		_modulesname[0] = "CShell.dll";
		_modulesname[1] = "crossfire.exe";
		f.open("jija.txt", std::ios::out);
	}

	DWORD getoffsets(const char* pattern, int length, int moduleid)
	{
		auto ptr = FindPatternInModuleProtect(
			CrtVec(pattern, length),
			_modulesname[moduleid]
		);

		/*auto ptr = FindPatternInModule(
			CrtVec(pattern, length),
			_modulesname[moduleid]
		);*/

		f << ptr << "\n";

		return (DWORD)ptr - _modules[moduleid];
	}
};