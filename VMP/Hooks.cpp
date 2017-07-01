/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Hooks.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: VMP client hooks
=============================================================*/


#include "Main.h"

CIDirect3D9			*pD3D;
typedef IDirect3D9 *(WINAPI* Direct3DCreate9_t)(UINT nSDKVersion);
Direct3DCreate9_t   pfn_Direct3DCreate9;

typedef HRESULT (WINAPI* DirectInput8Create_t)(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter);
DirectInput8Create_t pfn_DirectInput8Create;

typedef HRESULT (WINAPI* CreateProcess_t)(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation);
CreateProcess_t pfn_CreateProcess;


// Hook for the Direct3DCreate9 function
IDirect3D9* WINAPI Direct3DCreate9_Hook(UINT uSDKVersion)
{
	if(!pfn_Direct3DCreate9) 
		return NULL;

	// Call the function
	IDirect3D9 *pIDirect3D9 = pfn_Direct3DCreate9(uSDKVersion);
	if(pIDirect3D9)
	{
		// Create our fake class
		pD3D = new CIDirect3D9(pIDirect3D9);
		// Return
		return (pD3D ? pD3D : NULL);
	}
	return NULL;
}
// Hook for the CreateProcess function
BOOL WINAPI CreateProcess_Hook(LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes,
	BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation)
{
	// Suspend the process creation
	dwCreationFlags |= CREATE_SUSPENDED;
	// Create the game process
	if(!pfn_CreateProcess(lpApplicationName, lpCommandLine, lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment, lpCurrentDirectory, lpStartupInfo, lpProcessInformation))
	{
		MessageBox(NULL, "Cannot launch game", "V:MP Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Try to inject the library
	if(!InjectLibrary(lpProcessInformation->hProcess, "VMP.dll"))
	{
		MessageBox(NULL, "Cannot Inject library \"VMP.dll\" into game executable \"GTAIV.exe\"", "V:MP Error", MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}
	// Resume the launcher 
	ResumeThread(lpProcessInformation->hThread);
	// Return succeeded
	return TRUE;
}

HRESULT WINAPI DirectInput8Create_Hook(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID *ppvOut, LPUNKNOWN punkOuter)
{
	if(!pfn_DirectInput8Create) 
		return NULL;

	// Call the function
	HRESULT hr = pfn_DirectInput8Create(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	// Create our fake class
	*ppvOut = new CDirectInput8((CDirectInput8 *)*ppvOut);
	// Return
	return hr;
}

void CHooks::InstallHooks()
{
	// Are we installing Launcher or game hooks ?
	if(GetModuleHandle("LaunchGTAIV.exe") != NULL)
	{
		// Install CreateProcess hook
		pfn_CreateProcess = (CreateProcess_t)InstallDetoursHook(DetourFindFunction("Kernel32.dll", "CreateProcessW"), 
			(PBYTE)CreateProcess_Hook);
	}
	else
	{
		// Install the Xlive hook
		InstallXLiveHook();
		// Install Direct3D9 hook
		pfn_Direct3DCreate9 = (Direct3DCreate9_t)InstallDetoursHook(DetourFindFunction("d3d9.dll", "Direct3DCreate9"), 
			(PBYTE)Direct3DCreate9_Hook);

		// Install DirectInput8 hook
		pfn_DirectInput8Create = (DirectInput8Create_t)DetourFunction(DetourFindFunction("dinput8.dll", "DirectInput8Create"), 
			(PBYTE)DirectInput8Create_Hook);
	}
}

void CHooks::UninstallHooks()
{
	// Uninstall Direct3D9 hook
	DetourRemove(NULL, (PBYTE)pfn_Direct3DCreate9); 
}

PBYTE CHooks::InstallDetoursHook(PBYTE pbyteInstallAddress, PBYTE pbyteHookAddress)
{
	return DetourFunction(pbyteInstallAddress, pbyteHookAddress);
}

void CHooks::InstallCallHook(DWORD dwInstallAddress, DWORD dwHookFunction)
{
	// Unprotect the address
	UnProtect(dwInstallAddress, 5);
	// Calculate the installing address
	DWORD dwFunction = dwHookFunction - (dwInstallAddress + 5);
	// Write the call instruction
	*(BYTE *)dwInstallAddress = 0xE8;
	// Write the hook function address
	*(DWORD *)(dwInstallAddress + 1) = dwFunction;
}

void CHooks::InstallJmpHook(DWORD dwInstallAddress, DWORD dwHookFunction)
{
	// Unprotect the address
	UnProtect(dwInstallAddress, 5);
	// Calculate the installing address
	DWORD dwFunction = dwHookFunction - (dwInstallAddress + 5);
	// Write the call instruction
	*(BYTE *)dwInstallAddress = 0xE9;
	// Write the hook function address
	*(DWORD *)(dwInstallAddress + 1) = dwFunction;
}

void CHooks::InstallAddressHook(DWORD dwInstallAddress, DWORD dwHookFunction)
{
	// Unprotect the address
	UnProtect(dwInstallAddress, 5);
	// Write the hook function address
	*(DWORD *)(dwInstallAddress) = dwHookFunction;
}
