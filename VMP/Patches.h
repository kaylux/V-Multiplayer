/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Patches.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game patches header file
=============================================================*/

#ifndef PATCHES_H
#define PATCHES_H

class CPatches
{
	public:
		static void InstallFunctionDisablePatch(DWORD dwFunction, BYTE byteReturn);
		static void InstallCustomPatch(DWORD dwAddress, BYTE bytePatch[], int iLength);
		static void InstallNopPatch(DWORD dwAddress);

		static void InstallPatches();

};

#endif