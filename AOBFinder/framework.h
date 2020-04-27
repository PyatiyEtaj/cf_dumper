#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tlhelp32.h>
#include <winternl.h>
#include <Psapi.h>
#include "stdio.h"
#include <string>
#include <vector>
#include <fstream>
#include <functional>
#include <unordered_map>


std::vector<BYTE> CrtVec(const char* str, int length);

PBYTE FindPattern(
	const std::vector<BYTE>& pattern, PBYTE start, PBYTE end,
	std::function<PBYTE(PBYTE)> f = [](PBYTE ptr) -> PBYTE {return ptr; }
);

MODULEINFO GetModuleInfo(const char* szModule);

PBYTE FindPatternInModule(
	std::vector<BYTE> pattern,
	LPCSTR moduleName = NULL,
	DWORD startAdr = 0, DWORD endAdr = 0,
	std::function<PBYTE(PBYTE)> f = [](PBYTE ptr) -> PBYTE {return ptr; }
);