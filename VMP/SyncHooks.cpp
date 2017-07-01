/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: SyncHooks.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Sync hooks source file
=============================================================*/

#include "Main.h"

extern CGame			*pGame;

CVPlayerPed		*CSyncHooks::pPlayerPed = NULL;
CVPad			*CSyncHooks::pPad = NULL;
CVPad			CSyncHooks::oldPad;

void _declspec(naked) CPlayer__ProcessKeys_Hook()
{
	// Get the player ped pointer
	_asm
	{
		mov CSyncHooks::pPlayerPed, ecx
		pushad
	}
	// Is this the local player ?
	if(CSyncHooks::pPlayerPed == pGame->GetLocalPlayer()->GetPlayerPed()->GetHandler())
	{
		// Process the keys
		_asm
		{
			popad
			mov ecx, CSyncHooks::pPlayerPed
			call CAddress::FUNC_CPed__ProcessKeys
			pushad
		}
	}
	else
	{
		// Get player id from player ped
		EntityId playerId = pGame->GetPlayerManager()->GetPlayerIdFromPlayerPed(CSyncHooks::pPlayerPed);
		// Make sure its valid
		if(playerId != INVALID_PLAYER_ID)
		{
			// Save local player keys
			CSyncHooks::pPad = pGame->GetPad()->GetHandler();
			// Save the local player pad
			memcpy(&CSyncHooks::oldPad, CSyncHooks::pPad, sizeof(CVPad));
			// Reset the pad structure (We handle sync manually)
			for(BYTE i = 0; i < 188; i++)
			{
				CSyncHooks::pPad->pads[i].byteCurrentValue = 0;
				CSyncHooks::pPad->pads[i].byteLastValue = 0;
			}
			// Set the current player id to the current processing player
			pGame->SetCurrentPlayerIndex(pGame->GetPlayerManager()->GetAt(playerId)->GetGameId());
			// Process the player
			_asm
			{
				popad
				mov ecx, CSyncHooks::pPlayerPed
				call CAddress::FUNC_CPed__ProcessKeys
				pushad
			}
			// Restore the current player id to the local player
			pGame->SetCurrentPlayerIndex(pGame->GetLocalPlayer()->GetGameId());
			// Restore the pad
			memcpy(CSyncHooks::pPad, &CSyncHooks::oldPad, sizeof(CVPad));
		}
	}

	_asm 
	{
		popad
		ret
	}
}

void CSyncHooks::InstallSyncHooks()
{
	// Hook for CPlayer__ProcessKeys
	CHooks::InstallAddressHook(CAddress::CALLBACK_CPlayer__ProcessKeys, (DWORD)CPlayer__ProcessKeys_Hook);
}