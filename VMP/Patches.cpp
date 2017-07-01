/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Patches.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game patches source file
=============================================================*/

#include "Main.h"

extern CGame		*pGame;

void CPatches::InstallFunctionDisablePatch(DWORD dwFunction, BYTE byteReturn = 0)
{
	// Unprotect the the function
	UnProtect(dwFunction, byteReturn == 0 ? 1 : 2);
	// Write a retn patch
	*(BYTE *)(dwFunction) = 0xC3;
	// Write the return value
	if(byteReturn != 0)
		*(BYTE *)(dwFunction + 1) = byteReturn;
}

void CPatches::InstallNopPatch(DWORD dwAddress)
{
	// Unprotect the the address
	UnProtect(dwAddress, 5);
	// Write a NOP patch
	memset((LPVOID)dwAddress, 0x90, 5);
}

void CPatches::InstallCustomPatch(DWORD dwAddress, BYTE bytePatch[], int iLength)
{
	// Unprotect the address
	UnProtect(dwAddress, iLength);
	// Write the patch
	memcpy((LPVOID)dwAddress, bytePatch, iLength);
}

void CPatches::InstallPatches()
{
	// Disable population
	InstallFunctionDisablePatch(CAddress::CALLBACK_CPopulation__Process); 
	// Disable scenario peds
	BYTE byteScenarioPedsPatch[] = {0xC3, 0xC0, 0x33};
	InstallCustomPatch((pGame->GetBaseAddress() + 0x9FB9C0), byteScenarioPedsPatch, sizeof(byteScenarioPedsPatch));

	/* CPlayerInfo + 0x4BC == Player Control state */

}
