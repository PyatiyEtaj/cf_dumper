#pragma once
#include "framework.h"
#define LOG FALSE

enum ModulesNameEnum {
	CShell = 0,
	Crossfire = 1
};

class sigfnd {
private:
	DWORD _modules[2];
	const char* _modulesname[2];
#if LOG
	std::ofstream f;
#endif

public:
	sigfnd()
	{
		_modules[0] = (DWORD)GetModuleHandleA("CShell.dll");
		_modules[1] = (DWORD)GetModuleHandleA("crossfire.exe");
		_modulesname[0] = "CShell.dll";
		_modulesname[1] = "crossfire.exe";
#if LOG
		f.open("log.txt", std::ios::out);
#endif
	}

	PBYTE getptr(const char* pattern, int length, int moduleid)
	{
		return FindPatternInModule(
			CrtVec(pattern, length),
			_modulesname[moduleid]
		);
	}

	DWORD getoffsets(const char* pattern, int length, int moduleid)
	{
		auto ptr = FindPatternLight(
			CrtVec(pattern, length),
			_modulesname[moduleid]
		);

#if LOG
		f << ptr << "\n";
#endif

		return (DWORD)ptr - _modules[moduleid];
	}
};