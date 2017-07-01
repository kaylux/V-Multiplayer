/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: GameHooks.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game hooks source file
=============================================================*/

#include "Main.h"

// Reset CGameHooks variables
bool CGameHooks::m_bScriptInit = false;
bool CGameHooks::m_bScreenFaded = false;
bool CGameHooks::m_bMenuInit = false;

extern CGame			*pGame;
extern CConfig			*pConfig;

DWORD dwFunc = NULL;


void _declspec(naked) CScript__Process_Hook()
{
	_asm pushad

	// Call the process functions
	CGameHooks::CScript__Process();

	_asm 
	{
		popad
		mov al, 1
		retn
	}
}

void CGameHooks::CScript__Process()
{
	// Have we already been initialized ?
	if(!m_bScriptInit)
	{
		// Create the local player
		unsigned int uiPlayer = NULL;
		unsigned int *puiPlayer = &uiPlayer;
		float fX = -341.36f, fY = 1144.80f, fZ = 14.79f;//756.7745f, fY = -214.4033f, fZ = 4.822300f;
		_asm
		{
			push puiPlayer
			push fZ
			push fY
			push fX
			push 0
			call CAddress::FUNC_CreatePlayer
			add esp, 20
		}
		// Initialize the game
		pGame->InitializeInGame(uiPlayer);
		// Mark the script initialized
		m_bScriptInit = true;
	}
	else
	{
		// Fade the screen if its not faded yet
		if(!m_bScreenFaded)
		{
			// Fade the screen in
			pGame->Fade(0, FADE_TYPE_IN);
			// Mark the screen as faded
			m_bScreenFaded = true;
		}
		// Process the game
		pGame->Process();
	}
	
}

DWORD dwGameState = NULL;
DWORD gameState = 0;
DWORD laststate = -1;

void _declspec(naked) SetGameState_Hook()
{
	_asm 
	{
		pushad
		push eax
		mov eax, [esp+4]
		mov gameState, eax
		pop eax
	}

	if(gameState != laststate)
	{
		Log("gamestate: %d", gameState);
		laststate = gameState;
	}

	*(DWORD*)(pGame->GetBaseAddress() + 0x10C7F80) = gameState;
	_asm
	{
		popad
		mov al, 1
		retn
	}
}

void _declspec(naked) ProcessVehicleEntry_Hook()
{
	_asm
	{
		xor eax, eax
		retn 12
	}
}

void _declspec(naked) CTaskComplexExitVehicle__Constructor_Hook()
{
	_asm
	{
		xor eax, eax
		retn 16
	}
}

CVThread *pThread = NULL;

void _declspec(naked) GetActiveThread_Hook()
{
	pThread = pGame->GetActiveThread()->GetHandler();
	_asm
	{
		mov eax, pThread
		retn
	}
}

CVTask *pTask = NULL;
EntityId taskPlayerId = INVALID_PLAYER_ID;
DWORD dwTaskVFTable = NULL;

void _declspec(naked) CTask__Destructor_Hook()
{
	_asm
	{
		mov pTask, ecx
		pushad
	}
	// Find the player id from the task pointer
	if(pGame && pGame->GetPlayerManager())
	{
		taskPlayerId = pGame->GetPlayerManager()->GetPlayerIdFromTask(pTask);
		if(taskPlayerId != INVALID_PLAYER_ID)
			// Destroy the player's task
			pGame->GetPlayerManager()->GetAt(taskPlayerId)->HandleTaskDestroy();
		else
		{
			if(pGame->GetLocalPlayer()->GetTask() && pTask == pGame->GetLocalPlayer()->GetTask()->GetHandler()) 
				pGame->GetLocalPlayer()->HandleTaskDestroy();
		}
	}
	dwFunc = (pGame->GetBaseAddress() + 0xA288DA);
	dwTaskVFTable = (pGame->GetBaseAddress() + 0xD87224);
	_asm
	{
		popad
		mov ecx, pTask
		push esi
		mov esi, ecx
		push esi
		mov dword ptr [esi], offset dwTaskVFTable
		jmp dwFunc
	}

}

DWORD addr = NULL;

void _declspec(naked) WorldHook()
{
	_asm
	{
		mov eax, [esp]
		mov addr, eax
		pushad
	}

	Log("cr address : 0x%p", (addr - pGame->GetBaseAddress()));
	dwFunc = (pGame->GetBaseAddress() + 0x439F58);

	_asm
	{
		popad
		mov eax, [esp+12]
		mov edx, [esp+8]
		jmp dwFunc
	}
}

void CGameHooks::InstallGameHooks()
{
	// Hook for CScript__Process
	CHooks::InstallCallHook(CAddress::CALLBACK_CScript__Process, (DWORD)CScript__Process_Hook);
	// Hook for ProcessVehicleEntry
	CHooks::InstallJmpHook((pGame->GetBaseAddress() + 0x9B1ED0), (DWORD)ProcessVehicleEntry_Hook);
	// Hook for CTaskComplexExitVehicle__Constructor
	CHooks::InstallCallHook((pGame->GetBaseAddress() + 0x9BBC23), (DWORD)CTaskComplexExitVehicle__Constructor_Hook);
	// Hook for GetActiveThread
	CHooks::InstallJmpHook((pGame->GetBaseAddress() + 0x5A4CA0), (DWORD)GetActiveThread_Hook);
	// Hook for CTask__Destructor
	CHooks::InstallJmpHook((pGame->GetBaseAddress() + 0xA288D0), (DWORD)CTask__Destructor_Hook);

	//CHooks::InstallJmpHook((pGame->GetBaseAddress() + 0x439F50), (DWORD)WorldHook);
	

	// Hook for SetGameState
	//CHooks::InstallJmpHook((pGame->GetBaseAddress() + 0x7870A0), (DWORD)SetGameState_Hook);
	/*UnProtect((pGame->GetBaseAddress() + 0x7870A6), 1);
	*(BYTE *)(pGame->GetBaseAddress() + 0x7870A6)*/
}