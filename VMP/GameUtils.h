/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: GameUtils.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Game utils handler header file
=============================================================*/

#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include "Address.h"
#include "VPlayerInfo.h"
#include "VBlipInfo.h"
#include "Pools.h"
#include <SharedUtility.h>


// Enumerations
enum eFadeType
{
	FADE_TYPE_IN,
	FADE_TYPE_IN_UNHACKED,
	FADE_TYPE_OUT,
	FADE_TYPE_OUT_UNHACKED
};

// Game state enumeration
enum eGameState
{
	GAME_STATE_LOADING_SCREEN,
	GAME_STATE_MAIN_MENU,
	GAME_STATE_LOADING_GAME,
	GAME_STATE_PLAYING,
	GAME_STATE_PAUSED
};

// From Multi Theft Auto
enum eTaskPriority
{
	TASK_PRIORITY_PHYSICAL_RESPONSE,
	TASK_PRIORITY_EVENT_RESPONSE_TEMP,
	TASK_PRIORITY_EVENT_RESPONSE_NONTEMP,
	TASK_PRIORITY_PRIMARY,
	TASK_PRIORITY_DEFAULT,
	TASK_PRIORITY_MAX
};

enum ePadKeys
{
	PAD_NEXT_CAMERA,                      
	PAD_SPRINT,                          
	PAD_JUMP,                            
	PAD_ENTER                            
};

#define INVALID_PLAYER_INDEX (-1)
#define PLAYER_MODEL_INDEX 211

#define MODELS_NUMBER 65535
#define MAX_GAME_BLIPS 1500

class CGameUtils
{
	public:

		static CVPlayerInfo *GetPlayerInfoFromIndex(unsigned int uiPlayerIndex)
		{
			CVPlayerInfo *pPlayerInfo = NULL;
			_asm
			{
				push uiPlayerIndex
				call CAddress::FUNC_GetPlayerInfoFromIndex
				mov pPlayerInfo, eax
				add esp, 4
			}
			return pPlayerInfo;
		};

		static unsigned int GetModelIndexFromName(char *szModelName)
		{
			// Get the model index from name
			unsigned int uiModelIndex = 0;
			_asm
			{
				push szModelName
				call CAddress::FUNC_GetModelIndexFromName
				mov uiModelIndex, eax
				add esp, 4
			}
			// Return the model index
			return uiModelIndex;
		};

		static DWORD GetModelHashFromIndex(unsigned int uiModelIndex)
		{
			// Get the model hash from index
			DWORD dwModelHash = -1;
			DWORD *pdwModelHash = &dwModelHash;
			_asm
			{
				push pdwModelHash
				push uiModelIndex
				call CAddress::FUNC_GetModelHashFromIndex
				add esp, 8
			}
			// Return the model hash
			return dwModelHash;
		};

		static int GetFreePlayerSlot()
		{
			// Loop through the game player handles
			for(int i = 0; i < 32; i++)
			{
				// Get the player info
				CVPlayerInfo *pPlayerInfo = GetPlayerInfoFromIndex(i);
				if(pPlayerInfo == NULL || pPlayerInfo->pPlayerPed == NULL)
					return i;
			}
			return INVALID_PLAYER_INDEX;
		};

		static CVModel *GetModelInfoFromIndex(unsigned int uiModelIndex)
		{
			if(uiModelIndex >= 0 && uiModelIndex < MODELS_NUMBER)
				return *(CVModel **)(CAddress::ARRAY_ModelInfo + (uiModelIndex * 4));

			return NULL;
		};

		static CVBlipInfo *GetBlipInfoFromIndex(unsigned int uiBlipIndex)
		{
			if(uiBlipIndex >= 0 && uiBlipIndex < MAX_GAME_BLIPS)
				return *(CVBlipInfo **)(CAddress::ARRAY_BlipInfo + (uiBlipIndex * 4));

			return NULL;
		};

		static CVThread *GetThreadHandleFromIndex(unsigned int uiIndex)
		{
			CVThread *pThread = NULL;
			_asm
			{
				push uiIndex
				call CAddress::FUNC_GetThreadHandleFromIndex
				mov pThread, eax
			}
			return pThread;

		};


};

#endif