#include "framework.h"
#include "ReaderWriterBin.h"
#include "sigfnd.h"


std::vector<int> GetOffsets()
{
	sigfnd s;
	std::vector<int> vec;
	//SkinChanger
	vec.push_back(s.getoffsets("\x55\x8B\xEC\x66\x8B\x4D\x08\x66\x83\xF9\xFF", 11, ModulesNameEnum::CShell));

	vec.push_back(s.getoffsets("\xE8\x00\x00\x00\x00\x83\xC4\x04\x50\xE8\x00\x00\x00\x00\x8B\xF0\x83\xC4\x04", 19, ModulesNameEnum::CShell));
	vec.push_back(vec[vec.size() - 1] - 0x12);
	vec.push_back(s.getoffsets("\xE8\x39\xA8\xE1\xFF\x8B\xF8\x83\xC4\x04\x85\xFF\x0F\x84\xA1\x0A\x00\x00\x68\xA5", 20, ModulesNameEnum::CShell));
	// trouble
	//vec.push_back(s.getoffsets("\xE8\x00\x00\x00\x00\x8B\xF8\x83\xC4\x04\x85\xFF\x0F\x84\x00\x00\x00\x00\x68\xA5\x00\x00\x00\x8D\x85\x8A\xFE\xFF\xFF", 29, ModulesNameEnum::CShell));
	//vec.push_back(0);

	vec.push_back(s.getoffsets("\xE8\x00\x00\x00\x00\x8B\xF0\x83\xC4\x04\x85\xF6\x0F\x84\x00\x00\x00\x00\xF3\x0F\x10\x86\x00\x00\x00\x00\xF3\x0F\x11", 29, ModulesNameEnum::CShell));

	//vec.push_back(s.getoffsets("\x6A\x01\x56\x6A\x00\xFF\x90\x50\x01\x00\x00\x83\x7D\xEC\x10\x8D", 16, ModulesNameEnum::CShell) - 0x5F);
	vec.push_back(s.getoffsets("\xE8\x00\x00\x00\x00\x8B\xF0\x83\xC4\x04\x85\xF6\x0F\x84\x06\x01\x00\x00\x68\x00\x00\x00\x00\x8D\x4D\xC0\xE8", 27, ModulesNameEnum::CShell));

	//HitBoxes
	vec.push_back(s.getoffsets("\x8B\x0D\x00\x00\x00\x00\x81\xFE", 8, ModulesNameEnum::CShell) + 0x2);
	vec.push_back(s.getoffsets("\x69\xC1\x9C\x00\x00\x00\x03\x05\x00\x00\x00\x00\x5D\xC3\x33\xC0\x5D\xC3", 18, ModulesNameEnum::CShell) - 0x1C);
	vec.push_back(s.getoffsets("\xE8\x00\x00\x00\x00\x83\xC4\x04\x85\xC0\x74\x18\x68\x9C\x00\x00\x00\x50\x6A\x00\xE8", 21, ModulesNameEnum::CShell));

	//DIP
	vec.push_back(s.getoffsets("\x8B\x07\xFF\x75\x18", 5, ModulesNameEnum::Crossfire));

	//Esp
	vec.push_back(s.getoffsets("\x55\x8B\xEC\x51\xA1\x00\x00\x00\x00\x53\x8B\x5D\x08\x56", 14, ModulesNameEnum::CShell));
	//Bh
	vec.push_back(s.getoffsets("\x0F\xB6\x05\x00\x00\x00\x00\x8B\xCF\x50\x8D", 11, ModulesNameEnum::CShell) + 0x3);

	//BPI
	vec.push_back(s.getoffsets("\x55\x8B\xEC\x8B\x4D\x08\x85\xC9\x78\x18\xA1", 11, ModulesNameEnum::CShell));
	vec.push_back(s.getoffsets("\xE8\x00\x00\x00\x00\x8B\x5D\x0C\x83\xC4\x04\x85\xC0\x74\x18\x68\xA8\x00\x00\x00\x50\x6A\x00\xE8", 24, ModulesNameEnum::CShell));

	//Skins
	vec.push_back(s.getoffsets("\x55\x8B\xEC\x8B\x4D\x08\x83\xF9\x01\x7C\x18", 11, ModulesNameEnum::CShell));

	//textures
	vec.push_back(s.getoffsets("\x55\x8B\xEC\x8B\x4D\x08\x85\xC9\x78\x1D\xA1", 11, ModulesNameEnum::CShell));

	// CLTClient_this
	//vec.push_back(s.getoffsets("\x55\x8B\xEC\x51\x83\x3D\x00\x00\x00\x00\x00\x75\x11\x83\x3D", 15, ModulesNameEnum::Crossfire));

	return vec;
}

void Start_t(void* arg)
{
	ReaderWriterBin r;
	auto vec = GetOffsets();
	r.Write("Bytes//aob.data", vec);
	Beep(200, 200);
	ExitThread(0);
}

bool isActivated = false;

LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0 || isActivated)
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	isActivated = true;
	if (GetModuleHandleA("CShell.dll"))
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start_t, 0, 0, 0);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	DisableThreadLibraryCalls(hModule);
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

