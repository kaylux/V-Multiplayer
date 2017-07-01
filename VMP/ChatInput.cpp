/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ChatInput.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Client chatinput source file
=============================================================*/

#include "Main.h"

extern CClient		*pClient;
extern CGame		*pGame;

CChatInput::CChatInput(IDirect3DDevice9 *pDevice)
{
	// Save the device
	m_pDevice = pDevice;
	// Reset values
	m_bEnabled = false;
	m_byteLength = 0;
	m_byteCharacter = 0;
	strcpy(m_szText, "");
	m_dwLastTick = GetTickCount();
	m_bSlice = true;
	// Create fonts
	m_pSliceFont = new CFont(pDevice, 18, "Arial", FW_NORMAL);
	m_pFont = new CFont(pDevice, 22, "Arial", FW_NORMAL);
}

CChatInput::~CChatInput()
{
	// Delete fonts
	SAFE_DELETE(m_pSliceFont);
	SAFE_DELETE(m_pFont);
}

void CChatInput::AddInput(char cInput)
{
	// Make sure the character are valid
	if(cInput == (char)VK_RETURN || cInput == (char)VK_ESCAPE || cInput == (char)VK_BACK || m_byteLength > MAX_INPUT)
		return;

	// Check if we have to add or change a char
	if(m_byteCharacter != m_byteLength)
	{
		// Get the text before and after the character position
		char szAfter[MAX_INPUT], szBefore[MAX_INPUT];
		strcpy(szAfter, ""); 
		strcpy(szBefore, "");
		// Get the text after the character
		strcpy(szAfter, m_szText+m_byteCharacter);
		// Get the text before the character
		CopyString(m_szText, szBefore, m_byteCharacter);
		// Set the before text with the character
		sprintf(m_szText, "%s%c", szBefore, cInput);
		// Add the after text
		strcat(m_szText, szAfter);
	}
	else
	{
		// Add that character to the text
		m_szText[m_byteCharacter] = cInput;
	}
	// Increase the length
	m_byteLength++;
	// Increase the character place
	m_byteCharacter++;
	// Add the end of the string
	m_szText[m_byteLength] = '\0';
}

void CChatInput::DeleteInput()
{
	// If we have nothing to delete then dont go any further
	if(m_byteCharacter <= 0|| m_byteLength <= 0)
		return;

	// If we need to delete from a character position
	if(m_byteCharacter != m_byteLength)
	{
		// Loop through the text statring from the character postion
		for(unsigned int i = m_byteCharacter; i <= m_byteLength; i++)
		{
			m_szText[i-1] = m_szText[i];
		}
	}
	// Decrease the length
	m_byteLength--;
	// Decrease the character place
	m_byteCharacter--;
	// Add the end of the string
	m_szText[m_byteLength] = '\0';
}

void CChatInput::Right()
{
	// Make sure the character dosent go above the length
	if(m_byteCharacter >= m_byteLength)
		return;

	// Increase the character position
	m_byteCharacter++;
}

void CChatInput::Left()
{
	// Make sure the character dosent go under 0
	if(m_byteCharacter <= 0)
		return;

	// Decrease the character position
	m_byteCharacter--;
}


void CChatInput::Render()
{
	// Make sure the chatinput is enabled
	if(!m_bEnabled)
		return;

	float fX = 430.0f;
	float fY = 70.0f;
	// Add the ">" to the text
	char szText[MAX_INPUT+3];
	sprintf(szText, "> %s", m_szText);
	// Calculate if we need to toggle the slice
	if((GetTickCount() - m_dwLastTick) > 600)
	{
		m_bSlice = !m_bSlice;
		m_dwLastTick = GetTickCount();
	}
	// Render the text
	m_pFont->DrawText(szText, 0xFF000000, fX-1, fY);
	m_pFont->DrawText(szText, 0xFF000000, fX+1, fY);
	m_pFont->DrawText(szText, 0xFF000000, fX, fY-1);
	m_pFont->DrawText(szText, 0xFF000000, fX, fY+1);
	m_pFont->DrawText(szText, 0xFFFFFFFF, fX, fY);
	// If we need to render the sloce
	if(m_bSlice)
	{
		RECT rect;
		char szPlace[MAX_INPUT+2];
		// Get text until the current character position
		CopyString(szText, szPlace, m_byteCharacter+2);
		szPlace[strlen(szPlace)] = '\0';
		// Render it to get its rect place
		m_pFont->GetFont()->DrawText(NULL, szPlace, -1, &rect, DT_CALCRECT, 0xFF000000);
		// Calculate the place
		fY = (float)(70.0f+(rect.right - rect.left));
		// Render the slice
		m_pSliceFont->DrawText("|", 0xFF000000, fX-1, fY);
		m_pSliceFont->DrawText("|", 0xFF000000, fX+1, fY);
		m_pSliceFont->DrawText("|", 0xFF000000, fX, fY-1);
		m_pSliceFont->DrawText("|", 0xFF000000, fX, fY+1);
		m_pSliceFont->DrawText("|", 0xFFFFFFFF, fX, fY);
	}
}
extern CChatBox *pChatBox;
bool bMove = false;

CTask *pTask;
CVTask *pTaskHandler;
extern CBlipInfo *pTest;

void CChatInput::HandleInput()
{
	// Make sure we have something valid
	if(!m_szText || !m_byteLength)
		return;

	if(!strcmp(m_szText, "/player"))
	{
		pChatBox->AddMessage(LINE_TYPE_INFO, "", 0x0, 0xFFFFFFFF, "Creating fake player ...");
		pGame->GetPlayerManager()->AddPlayer(1, "player");
		Log("player created");
		pGame->GetPlayerManager()->GetAt(1)->Spawn(211);
		Log("spawn");
		pGame->GetPlayerManager()->GetAt(1)->GetPlayerPed()->SetPosition(CVector3(-341.36f, 1144.80f, 14.79f));
		Log("pos set");
		pChatBox->AddMessage(LINE_TYPE_INFO, "", 0x0, 0xFFFFFFFF, "Fake player successfully created and spawned");
	}

	if(!strcmp(m_szText, "/move"))
	{
	/*	Log("cr task");
		CTask *pMove = CSimpleTasks::CreateGoToPointTask(CVector3(-370.36f, 1144.80f, 14.79f), false);
		Log("done task 0x%x", pMove);
		pGame->GetPlayerManager()->GetAt(1)->GetPlayerPed()->SetPedTask(pMove, TASK_PRIORITY_MAX, false);
		Log("player tasked");*/
	}

	if(!strcmp(m_szText, "/blip"))
	{
		CVector3 *pvecPos = pTest->GetBlipPosition();
		Log("index: %d - pos (%f - %f - %f) - color %d - alpha %d - sprite %d", pTest->GetBlipAttachedEntityIndex(), pvecPos->fX, pvecPos->fY, pvecPos->fZ, pTest->GetBlipColor(),
			pTest->GetBlipAlpha(), (int)pTest->GetBlipSprite());

		Log("blip index %d", pGame->GetPlayerManager()->GetAt(1)->GetPlayerPed()->GetHandler()->iBlipIndex);
	}
	if(!strcmp(m_szText, "/delete"))
	{
		//pGame->GetPlayerManager()->GetAt(1)->GetBlip(
	}
	if(!strcmp(m_szText, "/eveh"))
	{
		pGame->GetPlayerManager()->GetAt(1)->EnterVehicle(0, 0);
	}
	if(!strcmp(m_szText, "/exveh"))
	{
		pGame->GetPlayerManager()->GetAt(1)->ExitVehicle(0);
	}
	// Make sure the chatinput is enabled & we are playing
	if(pClient->GetNetworkState() == NET_STATE_PLAYING && m_bEnabled)
	{
		// Send message to the server
		BitStream bitStream;
		bitStream.Write(m_szText);
		// Check if it is a command or chat
		if(m_szText[0] == '/')
			pClient->RPC(RPC_COMMAND, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
		else
			pClient->RPC(RPC_CHAT_MESSAGE, &bitStream, HIGH_PRIORITY, RELIABLE_ORDERED, 0, INVALID_PLAYER_ID, true);
	}
	// Reset everything
	strcpy(m_szText, "");
	m_byteLength = 0;
	m_byteCharacter = 0;
	Toggle();
}

void CChatInput::Toggle()
{
	// Toggle chatinput
	m_bEnabled = !m_bEnabled;
	// Toggle game keys
	pGame->ToggleKeys(!m_bEnabled);
}

void CChatInput::OnLostDevice()
{
	m_pFont->GetFont()->OnLostDevice();
	m_pSliceFont->GetFont()->OnLostDevice();
}

void CChatInput::OnResetDevice()
{
	m_pFont->GetFont()->OnResetDevice();
	m_pSliceFont->GetFont()->OnResetDevice();
}