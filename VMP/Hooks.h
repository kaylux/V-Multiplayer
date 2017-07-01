/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Hooks.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: VMP client hooks
=============================================================*/

#ifndef HOOKS_H
#define HOOKS_H

class CHooks
{
	public:
		static void InstallHooks();
		static void UninstallHooks();

		/////////////////////////////////////////////////////////////////////////////////////////
		static PBYTE InstallDetoursHook(PBYTE pbyteInstallAddress, PBYTE pbyteHookAddress);
		static void InstallCallHook(DWORD dwInstallAddress, DWORD dwHookFunction);
		static void InstallJmpHook(DWORD dwInstallAddress, DWORD dwHookFunction);
		static void InstallAddressHook(DWORD dwInstallAddress, DWORD dwHookFunction);


};

#endif