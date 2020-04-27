#include "framework.h"

std::vector<BYTE> CrtVec(const char* str, int length)
{
	std::vector<BYTE> vec;
	for (int i = 0; i < length; i++)
	{
		vec.emplace_back(str[i]);
	}
	return vec;
}

bool __compare(const std::vector<BYTE>& b, PBYTE pos)
{
	for (size_t i = 0; i < b.size(); i++)
	{
		if (b[i] != 0x0 && b[i] != pos[i])
		{
			return false;
		}
	}
	return true;
}

PBYTE FindPattern(
	const std::vector<BYTE>& pattern, PBYTE start, PBYTE end,
	std::function<PBYTE(PBYTE)> f
)
{
	end -= pattern.size();
	int endI = pattern.size() - 1;
	int middle = endI / 2;
	for (; start < end; start++)
	{
		//printf_s("%X == %X | %X == %X | %X == %X |\n", start[0], pattern[0], start[middle], pattern[middle], start[endI], pattern[endI]);
		if (!(start[0] == pattern[0] || (pattern[0] == 0x0))) continue;
		if (!(start[middle] == pattern[middle] || (pattern[middle] == 0x0))) { start += middle; continue; }
		if (!(start[endI] == pattern[endI] || (pattern[endI] == 0x0))) { start += endI; continue; }

		if (__compare(pattern, start))
		{
			auto res = f(start);
			if (res != nullptr) return res;
		}
		else
		{
			//start += endI;
			start++;
		}
	}
	return nullptr;
}

MODULEINFO GetModuleInfo(const char* szModule)
{
	MODULEINFO modinfo = { 0 };
	HMODULE hModule = GetModuleHandleA(szModule);
	if (hModule == 0)
		return modinfo;
	GetModuleInformation(GetCurrentProcess(), hModule, &modinfo, sizeof(MODULEINFO));
	return modinfo;
}

PBYTE FindPatternInModule(
	std::vector<BYTE> pattern,
	LPCSTR moduleName,
	DWORD startAdr, DWORD endAdr,
	std::function<PBYTE(PBYTE)> f
)
{
	HANDLE hProc = GetCurrentProcess();
	MEMORY_BASIC_INFORMATION mbi;
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	MODULEINFO mInfo = GetModuleInfo(moduleName);
	//printf_s("0x%X %d\n", mInfo.lpBaseOfDll, mInfo.SizeOfImage);
	LPVOID lpMem = (startAdr == 0) ? mInfo.lpBaseOfDll : LPVOID(startAdr);
	LPVOID   end = (endAdr == 0) ? (LPVOID)((DWORD)lpMem + mInfo.SizeOfImage) : LPVOID(endAdr);
	if (startAdr != 0 && endAdr == 0)
	{
		end = si.lpMaximumApplicationAddress;
	}
	//printf_s("adr [ %X , %X ]\n", startAdr, endAdr);
	while (lpMem < end)
	{
		VirtualQueryEx(hProc, lpMem, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		DWORD oldprotect;
		//printf_s("adr [ %X , %X ]", lpMem, (DWORD)lpMem + mbi.RegionSize);
		if (VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &oldprotect))
		{
			//printf_s(" -- oldprotect %X   ", oldprotect);
			PBYTE ptr = FindPattern(pattern, (PBYTE)mbi.BaseAddress, (PBYTE)((DWORD)mbi.BaseAddress + (DWORD)mbi.RegionSize), f);
			if (ptr != nullptr) return ptr;
			DWORD __temp;
			VirtualProtect(mbi.BaseAddress, mbi.RegionSize, oldprotect, &__temp);
		}
		//printf_s("\n");
		lpMem = (LPVOID)((DWORD)mbi.BaseAddress + (DWORD)mbi.RegionSize);
	}
	return nullptr;
}