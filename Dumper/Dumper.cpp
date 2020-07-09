#include <Windows.h>
#include <iostream>

using namespace std;

#define WND_NAME "CROSSFIRE"

inline HHOOK SetWndHook(int hookType, HMODULE h, LPCSTR funcName, DWORD thread)
{
	return SetWindowsHookEx(hookType, (HOOKPROC)GetProcAddress(h, funcName), h, thread);
}

// By Global HOOK
HHOOK InstallHook(HMODULE pDll, LPCSTR wndName)
{
	HWND cfwnd = FindWindowA(NULL, wndName);

	HHOOK hhook = SetWndHook(5, pDll, "HookProc", 0);

	if (GetLastError() != 0)
	{
		string s = "something wrong --> " + GetLastError();
		cout << s << endl;
		return NULL;
	}
	cout << "HOOK " << hhook << " have setted" << endl;
	SendMessage(cfwnd, WM_MOUSEMOVE, MK_LBUTTON, NULL);

	return hhook;
}

void InjectionGlobalHook()
{
	Sleep(10000);

	HMODULE pDll = LoadLibraryA("AOBFinder.dll");
	HHOOK hhk = InstallHook(pDll, WND_NAME);
	if (hhk)
	{
		system("pause");
		cout << "HOOK " << hhk << " released" << endl;
		UnhookWindowsHookEx(hhk);
	}
	else
		cout << "HOOK hasn't been setted" << endl;
	system("pause");
}

int main()
{
	//HWND hWnd = GetForegroundWindow();
	while (true)
	{
		if (FindWindowA(NULL, WND_NAME)) {
			InjectionGlobalHook();
			break;
		}

		if (GetAsyncKeyState(VK_SPACE) & 1)
			break;

		Sleep(200);
	}
	return 0;
}
