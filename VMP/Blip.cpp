/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Blip.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Blip class source file
=============================================================*/

#include "Main.h"

CBlip::CBlip(eBlipType type)
{
	// Save the blip type
	m_type = type;
	// Create the BlipInfo instance
	m_pBlipInfo = new CBlipInfo(NULL);
	// Reset blip index
	m_uiBlipIndex = 255; // TODO: Declare a constante of (INVALID_ENTITY_ID = 255) after verifying the game limits
	// Reset blip param
	m_iEntityIndex = INVALID_PLAYER_INDEX;
	m_vecPosition = CVector3();
}

CBlip::~CBlip()
{
	// Destroy the blip
	Destroy();
	// Delete the blip info instance
	SAFE_DELETE(m_pBlipInfo);
}

CBlipInfo *pTest;

extern CGame	*pGame;

void CBlip::Create()
{
	// Create the blip
	/*int iBlipType = (int)m_type;
	CVector3 vecPosition = m_vecPosition;
	int iEntityIndex = m_iEntityIndex;
	WORD wIndex = 0;
	char *szName = "player";
	_asm
	{
		push szName
		push 2
		push vecPosition
		push iEntityIndex
		push iBlipType
		push 1
		call CAddress::FUNC_CreateBlip
		mov wIndex, ax
		add esp, 24
	}
	if(wIndex < 0)
		return;*/

	DWORD dwFunc = (pGame->GetBaseAddress() + 0xBB42D0);
	WORD dwIndex = 0;
	WORD *pIndex = &dwIndex;
	int iEntityIndex = m_iEntityIndex;
	Log("creating blip for %d", iEntityIndex);
	_asm
	{
		push pIndex
		push iEntityIndex
		call dwFunc
		add esp, 8
	}
	Log("idx %d", dwIndex);
	// Set the blip game index
	m_uiBlipIndex = dwIndex;
	// Get the blip info
	CVBlipInfo *pBlipInfo = CGameUtils::GetBlipInfoFromIndex(m_uiBlipIndex);
	// Make sure the blip is successfully created
	if(pBlipInfo == NULL || pBlipInfo->bCreatedFlag == 0)
		return;

	// Set the blip info pointer
	m_pBlipInfo->SetHandler(pBlipInfo);
	/*// Set the blip sprite
	m_pBlipInfo->SetBlipSprite(BLIP_PLAYER);
	// Set blip color
	m_pBlipInfo->SetBlipColor(2);
	// Set the blip params
	m_pBlipInfo->SetBlipAlpha(m_pBlipInfo->GetBlipColor() & 0xFF);
	// Set blip size
	m_pBlipInfo->SetBlipScale(0);*/

	pTest = m_pBlipInfo;
}

void CBlip::Destroy()
{
	// Destroy the blip
	unsigned int uiBlipIndex = m_uiBlipIndex;
	_asm
	{
		push 0
		push uiBlipIndex
		call CAddress::FUNC_DeleteBlip
		add esp, 8
	}
}


