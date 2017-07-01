/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Model.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: models handler source file
=============================================================*/

#include "Main.h"

extern CGame	*pGame;

CModel::CModel(unsigned int uiModelIndex)
{
	// Save the model index
	m_uiModelIndex = uiModelIndex;
	// Reset values
	m_bLoaded = false;
	// Do we have a valid model index ?
	if(uiModelIndex >= 0)
	{
		// Create the model handler
		m_pModel = CGameUtils::GetModelInfoFromIndex(uiModelIndex);
		if(m_pModel)
			// Save the model hash
			m_dwModelHash = m_pModel->dwHash;
		else
		{
			// Reset model values
			m_pModel = NULL;
			m_dwModelHash = 0x0;
		}

	}
	else
	{
		// Reset model values
		m_pModel = NULL;
		m_dwModelHash = 0x0;
	}
}

CModel::~CModel()
{
	// Unload the model
	Unload();
}

bool CModel::Load(bool bWaitForLoad)
{
	// Make sure we have a model handler and its not loaded yet
	if(!m_pModel || IsLoaded())
		return true;

	// Well, we will be using V Request & Load model inhere
	// but for now lets use IV ones

	// Request the model
    unsigned int VAR_ResourceTypeModel = *(unsigned int *)(pGame->GetBaseAddress() + 0x15F73A0);
	unsigned int uiModelIndex = m_uiModelIndex;
	_asm
	{
		push 0x1A
		push VAR_ResourceTypeModel
		push uiModelIndex
		call CAddress::FUNC_RequestModel
		add esp, 12
	}
	// Load all the requested models 
	_asm
	{
		push 1
		call CAddress::FUNC_LoadRequestedModels
		add esp, 4
	}
	if(bWaitForLoad)
	{
		WORD wTick = 5000;
		while(!IsLoaded() && wTick > 0)
		{
			// Decrease the tick count
			wTick--;
			// Sleep 1ms
			Sleep(1);
		}
		// Return the load state
		return IsLoaded();
	}
	// Set the load state
	m_bLoaded = true;
	// Return true if we're not waiting for it to load
	return true;
}

bool CModel::IsLoaded()
{
	// If our model is already loaded, then dont go for game functions
	if(m_bLoaded)
		return true;

	// Call the IsResourceLoaded function
	unsigned int VAR_ResourceTypeModel = *(unsigned int *)(pGame->GetBaseAddress() + 0x15F73A0);
	unsigned int uiModelIndex = m_uiModelIndex;
	bool bReturn = false;
    _asm
    {
        push VAR_ResourceTypeModel
		push uiModelIndex
        call CAddress::FUNC_IsModelLoaded
		add esp, 8
        mov bReturn, al
    }
	// Set the load state
	m_bLoaded = bReturn;
	// Return the loaded state
    return bReturn;
}

void CModel::Unload()
{
	// TODO: Add that when have a game
}

