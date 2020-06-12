#include <windows.h>
#include <Shlwapi.h>
#include "tracker.h"
#include "hook.h"
#pragma comment(lib, "Shlwapi.lib")

#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=AheadLib_GetFileVersionInfoA,@1")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=AheadLib_GetFileVersionInfoByHandle,@2")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=AheadLib_GetFileVersionInfoExW,@3")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=AheadLib_GetFileVersionInfoSizeA,@4")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=AheadLib_GetFileVersionInfoSizeExW,@5")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=AheadLib_GetFileVersionInfoSizeW,@6")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=AheadLib_GetFileVersionInfoW,@7")
#pragma comment(linker, "/EXPORT:VerFindFileA=AheadLib_VerFindFileA,@8")
#pragma comment(linker, "/EXPORT:VerFindFileW=AheadLib_VerFindFileW,@9")
#pragma comment(linker, "/EXPORT:VerInstallFileA=AheadLib_VerInstallFileA,@10")
#pragma comment(linker, "/EXPORT:VerInstallFileW=AheadLib_VerInstallFileW,@11")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=KERNEL32.VerLanguageNameA,@12")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=KERNEL32.VerLanguageNameW,@13")
#pragma comment(linker, "/EXPORT:VerQueryValueA=AheadLib_VerQueryValueA,@14")
#pragma comment(linker, "/EXPORT:VerQueryValueW=AheadLib_VerQueryValueW,@15")


extern "C" {
 PVOID pfnAheadLib_GetFileVersionInfoA;
 PVOID pfnAheadLib_GetFileVersionInfoByHandle;
 PVOID pfnAheadLib_GetFileVersionInfoExW;
 PVOID pfnAheadLib_GetFileVersionInfoSizeA;
 PVOID pfnAheadLib_GetFileVersionInfoSizeExW;
 PVOID pfnAheadLib_GetFileVersionInfoSizeW;
 PVOID pfnAheadLib_GetFileVersionInfoW;
 PVOID pfnAheadLib_VerFindFileA;
 PVOID pfnAheadLib_VerFindFileW;
 PVOID pfnAheadLib_VerInstallFileA;
 PVOID pfnAheadLib_VerInstallFileW;
 PVOID pfnAheadLib_VerQueryValueA;
 PVOID pfnAheadLib_VerQueryValueW;
 void AheadLib_GetFileVersionInfoA(void);
 void AheadLib_GetFileVersionInfoByHandle(void);
 void AheadLib_GetFileVersionInfoExW(void);
 void AheadLib_GetFileVersionInfoSizeA(void);
 void AheadLib_GetFileVersionInfoSizeExW(void);
 void AheadLib_GetFileVersionInfoSizeW(void);
 void AheadLib_GetFileVersionInfoW(void);
 void AheadLib_VerFindFileA(void);
 void AheadLib_VerFindFileW(void);
 void AheadLib_VerInstallFileA(void);
 void AheadLib_VerInstallFileW(void);
 void AheadLib_VerQueryValueA(void);
 void AheadLib_VerQueryValueW(void);
};

static HMODULE	g_OldModule = NULL;

// 加载原始模块
__inline BOOL WINAPI Load()
{
	TCHAR tzPath[MAX_PATH];
	TCHAR tzTemp[MAX_PATH * 2];
	GetSystemDirectory(tzPath, MAX_PATH);  // 这里是否从系统目录加载或者当前目录，自行修改

	lstrcat(tzPath, TEXT("\\version.dll"));
	g_OldModule = LoadLibrary(tzPath);
	if (g_OldModule == NULL)
	{
		wsprintf(tzTemp, TEXT("无法找到模块 %s,程序无法正常运行"), tzPath);
		MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
	}

	return (g_OldModule != NULL);	
}

// 释放原始模块
__inline VOID WINAPI Free()
{
	if (g_OldModule)
	{
		FreeLibrary(g_OldModule);
	}
}
// 获取原始函数地址
FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
	FARPROC fpAddress;
	CHAR szProcName[128];
	TCHAR tzTemp[MAX_PATH];

	fpAddress = GetProcAddress(g_OldModule, pszProcName);
	if (fpAddress == NULL)
	{
		if (HIWORD(pszProcName) == 0)
		{
			wsprintfA(szProcName, "%d", pszProcName);
			pszProcName = szProcName;
		}

		wsprintf(tzTemp, TEXT("无法找到函数 %S,程序无法正常运行"), pszProcName);
		MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
		ExitProcess(-2);
	}
	return fpAddress;
}

// 初始化获取原函数地址
BOOL WINAPI Init()
{
	if(NULL == (pfnAheadLib_GetFileVersionInfoA = GetAddress("GetFileVersionInfoA")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoByHandle = GetAddress("GetFileVersionInfoByHandle")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoExW = GetAddress("GetFileVersionInfoExW")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoSizeA = GetAddress("GetFileVersionInfoSizeA")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoSizeExW = GetAddress("GetFileVersionInfoSizeExW")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoSizeW = GetAddress("GetFileVersionInfoSizeW")))
		return FALSE;
	if(NULL == (pfnAheadLib_GetFileVersionInfoW = GetAddress("GetFileVersionInfoW")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerFindFileA = GetAddress("VerFindFileA")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerFindFileW = GetAddress("VerFindFileW")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerInstallFileA = GetAddress("VerInstallFileA")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerInstallFileW = GetAddress("VerInstallFileW")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerQueryValueA = GetAddress("VerQueryValueA")))
		return FALSE;
	if(NULL == (pfnAheadLib_VerQueryValueW = GetAddress("VerQueryValueW")))
		return FALSE;
	return TRUE;
}

DWORD WINAPI ThreadProc(LPVOID lpThreadParameter)
{
	Initialize_Eye_Tracker();
	Start_Tracking_Thread();
	return TRUE;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		if (Load() && Init())
		{
			TCHAR szAppName[MAX_PATH] = TEXT("VRChat.exe");	//请改为相应的Dll宿主文件名
			TCHAR szFullPath[MAX_PATH] = { 0 };
			int nLength = 0;
			nLength = GetModuleFileName(NULL, szFullPath, MAX_PATH);
			PathStripPath(szFullPath);
			if (StrCmpI(szAppName, szFullPath) == 0) //这里是否判断宿主进程名?
			{
				CloseHandle(CreateThread(NULL, NULL, ThreadProc, NULL, NULL, NULL));

				Initialize_Hook();
			}
		}
		else
		{
			return FALSE;
		}
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		Stop_Tracking_Thread();
		Release_Eye_tracker();
		Free();
	}

	return TRUE;
}
