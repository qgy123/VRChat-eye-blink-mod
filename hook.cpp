#include <Windows.h>

#include "hook.h"
#include "detours.h"
#include "address.h"
#include "debug.h"
#include <fmt/core.h>
#include "tracker.h"
#include <time.h>

typedef HMODULE(WINAPI* PFN_LoadLibraryW)(_In_ LPCWSTR lpLibFileName);
PFN_LoadLibraryW OldLoadLibraryW = LoadLibraryW;

int(_cdecl* originalFunction1)(void* thiz, bool flag);
int(_cdecl* originalFunction2)(void* thiz, bool flag);
int(_cdecl* originalFunction3)(void* thiz, bool flag);
int(_cdecl* originalFunction4)(void* thiz, bool flag);
int(_cdecl* originalFunction5)(void* thiz, bool flag);

int _cdecl FakeFunction1(void* thiz, bool flag)
{
	int num = originalFunction1(thiz, flag);

	if (is_blink)
	{
		//DEBUG_OUT(fmt::format(L"GetControllGesture1 flag: {0}, returns: {1}\n", flag, num));
		return 103;
	}
	return num;
}

int _cdecl FakeFunction2(void* thiz, bool flag)
{
	int num = originalFunction2(thiz, flag);
	
	if (is_blink)
	{
		//DEBUG_OUT(fmt::format(L"GetControllGesture2 flag: {0}, returns: {1}\n", flag, num));
		return 103;
	}
	return num;
}

int _cdecl FakeFunction3(void* thiz, bool flag)
{
	int num = originalFunction3(thiz, flag);
	//DEBUG_OUT(fmt::format(L"GetControllGesture3 flag: {0}, returns: {1}\n", flag, num));
	return num;
}

int _cdecl FakeFunction4(void* thiz, bool flag)
{
	int num = originalFunction4(thiz, flag);
	//DEBUG_OUT(fmt::format(L"GetControllGesture4 flag: {0}, returns: {1}\n", flag, num));
	return num;
}

int _cdecl FakeFunction5(void* thiz, bool flag)
{
	int num = originalFunction5(thiz, flag);
	//DEBUG_OUT(fmt::format(L"GetControllGesture5 flag: {0}, returns: {1}\n", flag, num));
	return num;
}

HANDLE WINAPI FakeLoadLibraryW(
    _In_ LPCWSTR lpLibFileName
)
{
	DEBUG_OUT(fmt::format(L"LoadLibraryW: {}\n", lpLibFileName));
	
	const HANDLE h = OldLoadLibraryW(lpLibFileName);

	if (wcsstr(lpLibFileName, L"GameAssembly.dll") != nullptr)
	{
		if (h != nullptr)
		{
			originalFunction1 = (int(_cdecl*)(void* thiz, bool flag))((void *)((UINT64)h + ADDRESS_OFFEST1));
			originalFunction2 = (int(_cdecl*)(void* thiz, bool flag))((void *)((UINT64)h + ADDRESS_OFFEST2));
			originalFunction3 = (int(_cdecl*)(void* thiz, bool flag))((void *)((UINT64)h + ADDRESS_OFFEST3));
			originalFunction4 = (int(_cdecl*)(void* thiz, bool flag))((void *)((UINT64)h + ADDRESS_OFFEST4));
			originalFunction5 = (int(_cdecl*)(void* thiz, bool flag))((void *)((UINT64)h + ADDRESS_OFFEST5));

			DEBUG_OUT(fmt::format(L"originalFunction1 found at: {}\n", static_cast<void*>(originalFunction1)));
			DEBUG_OUT(fmt::format(L"originalFunction1 found at: {}\n", static_cast<void*>(originalFunction2)));
			DEBUG_OUT(fmt::format(L"originalFunction1 found at: {}\n", static_cast<void*>(originalFunction3)));
			DEBUG_OUT(fmt::format(L"originalFunction1 found at: {}\n", static_cast<void*>(originalFunction4)));
			DEBUG_OUT(fmt::format(L"originalFunction1 found at: {}\n", static_cast<void*>(originalFunction5)));

			DetourTransactionBegin();
			DetourUpdateThread(GetCurrentThread());
			DetourAttach((PVOID*)&originalFunction1, FakeFunction1);
			DetourAttach((PVOID*)&originalFunction2, FakeFunction2);
			DetourAttach((PVOID*)&originalFunction3, FakeFunction3);
			DetourAttach((PVOID*)&originalFunction4, FakeFunction4);
			DetourAttach((PVOID*)&originalFunction5, FakeFunction5);
			DetourTransactionCommit();
		}

		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)OldLoadLibraryW, FakeLoadLibraryW);
		DetourTransactionCommit();
	}

	return h;
}

void Initialize_Hook()
{
	int error = DetourTransactionBegin();
	if (error != NO_ERROR)
	{
		DEBUG_OUT(L"DetourTransactionBegin Error!\n");
	}

	error = DetourAttach((PVOID*)&OldLoadLibraryW, FakeLoadLibraryW);
	if (error != NO_ERROR)
	{
		DEBUG_OUT(L"Fail to hook LoadLibraryW!\n");
	}

	error = DetourUpdateThread(GetCurrentThread());
	if (error != NO_ERROR)
	{
		DEBUG_OUT(L"DetourUpdateThread Error!\n");
	}
	
	error = DetourTransactionCommit();
	if (error != NO_ERROR)
	{
		DEBUG_OUT(L"DetourTransactionCommit Error!\n");
	}
}
