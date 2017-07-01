/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: NameTags.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Client nametags handler source file
=============================================================*/

#include "Main.h"

extern CGame		*pGame;

CNameTags::CNameTags(IDirect3DDevice9 *pDevice)
{
	// Save the Direct3D device
	m_pDevice = pDevice;
	// Create the chatbox font
	m_pFont = new CFont(pDevice, 10, "Arial", FW_BOLD);
	// Set enabled by default
	m_bEnabled = true;
}

CNameTags::~CNameTags()
{
	// Delete the font instance
	SAFE_DELETE(m_pFont);
}

void CNameTags::Render()
{
	// Are we enabled ?
	if(m_bEnabled && pGame->GetPlayerManager())
	{	
		/*// Loop through the players
		for(EntityId i = 0; i < MAX_PLAYERS; i++)
		{
			// Is the player connected ?
			if(pGame->GetPlayerManager()->IsPlayerConnected(i))
			{
				// Get the player position
				CVector3 vecPlayerPos;
				pGame->GetPlayerManager()->GetAt(i)->GetPlayerPed()->GetPosition(vecPlayerPos);
				// Get local player position
				CVector3 vecLocalPos;
				pGame->GetLocalPlayer()->GetPlayerPed()->GetPosition(vecLocalPos);
				// Make sure the player is not too far away
				if((vecPlayerPos - vecLocalPos).Length() > 20.0f)
					continue;

				// Get the game viewport
				D3DVIEWPORT9 Viewport;
				HRESULT hRes = m_pDevice->GetViewport(&Viewport);
				// Get the game matrix identity
				D3DXMATRIX matIdentity;
				D3DXMatrixIdentity(&matIdentity);
				// Convert from world to screen using d3d projectile
				D3DXVECTOR3 vecScreen;
				D3DXVECTOR3 vecPos;
				vecPos.x = vecPlayerPos.fX;
				vecPos.y = vecPlayerPos.fY;
				vecPos.z = vecPlayerPos.fZ;
				// Get the distance from the target player to the local player (TODO: Change this to use a PlayerPed function)
				float fSX = (vecPlayerPos.fX - vecLocalPos.fX) * (vecPlayerPos.fX - vecLocalPos.fX);
				float fSY = (vecPlayerPos.fY - vecLocalPos.fY) * (vecPlayerPos.fY - vecLocalPos.fY);
				float fSZ = (vecPlayerPos.fZ - vecLocalPos.fZ) * (vecPlayerPos.fZ - vecLocalPos.fZ);
				float fDistance = (float)sqrt(fSX + fSY + fSZ);	
				// Calculate the Z coord
				vecPos.z += 0.7f + (fDistance * 0.05f);
				// Calculate the screen position based on the projection from world coords
				D3DXVec3Project(&vecScreen, &vecPos, &Viewport, &m_matProjection, &m_matView, &matIdentity);
				// Make sure it dosent write to somewhere else
				if(vecScreen.z > 1.0f)
					continue;

				RECT rScreen = {(int)vecScreen.x, (int)vecScreen.y, (int)vecScreen.x + 1, (int)vecScreen.y + 1};
				// Render the name tag
				char szPlayerName[MAX_NAME_LENGTH], szNameTag[MAX_NAME_LENGTH+6];
				pGame->GetPlayerManager()->GetAt(i)->GetName(szPlayerName);
				sprintf(szNameTag, "%s(%d)", szPlayerName, i);
				//m_pFont->DrawText(szNameTag, 0xFFFFFFFF, vecScreen.x, vecScreen.y);
				m_pFont->GetFont()->DrawText(NULL, szNameTag, -1, &rScreen, DT_NOCLIP, 0xFFFFFFFF);
			}
		}*/
	}

}

void CNameTags::OnLostDevice()
{
	m_pFont->GetFont()->OnLostDevice();
}

void CNameTags::OnRestDevice()
{
	m_pFont->GetFont()->OnResetDevice();
}

