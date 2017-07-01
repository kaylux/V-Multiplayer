/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ChatBox.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Client chatbox source file
=============================================================*/

#include "Main.h"

CChatBox::CChatBox(IDirect3DDevice9 *pDevice)
{
	// Save the Direct3D device
	m_pDevice = pDevice;
	// Create the chatbox font
	m_pFont = new CFont(pDevice, 15, "Verdenna", FW_NORMAL);
	// Reset values
	m_iCurrentLine = 0;
	m_iLines = 0;
	m_bEnabled = true;
	for(int i = 0; i <= MAX_LINES; i++)
		m_bCreated[i] = false;
}

CChatBox::~CChatBox()
{
	SAFE_DELETE(m_pFont);
}

void CChatBox::AddMessage(eLineType LineType, char *szPlayerName, D3DCOLOR dPlayerColor, D3DCOLOR dColor, char *szText, ...)
{
	// Make sure we dont get over the lines limit and we have a valid text
	if(m_iLines > MAX_LINES || !szText)
		return;

	// Copy the player nick
	strcpy(m_szNick[m_iLines], szPlayerName);
	// Get the message
	va_list vArgs;
	va_start(vArgs, szText);
	vsprintf(m_szLineText[m_iLines], szText, vArgs);
	va_end(vArgs);
	// Save the message color
	if(LineType == LINE_TYPE_INFO || LineType == LINE_TYPE_CHAT)
		m_dColor[m_iLines] = 0xFFFFFFFF;
	else
		m_dColor[m_iLines] = D3DCOLOR_ARGB(255, 0, 0, 200);
	
	if(dColor)
		m_dColor[m_iLines] = dColor;

	// Mark chatbox line as created
	m_bCreated[m_iLines] = true;
	// Save the chatbox line type
	m_LineType[m_iLines] = LineType;
	// Save the player color
	m_dNickColor[m_iLines] = dPlayerColor;
	// Check if it needs down
	if(m_iLines > MAX_LINES_PER_WINDOW && (m_iCurrentLine+MAX_LINES_PER_WINDOW+1) >= m_iLines)
		Down();

	// Increase the lines count
	m_iLines++;

}

void CChatBox::Render()
{
	// Make sure we can render
	if(m_iLines == 0 || !m_pFont || !m_bEnabled)
		return;

	// Setup position variables
	float fX = 130.0f;
	float fY = 40.0f;
	char szMsg[145];
	RECT NickRect;
	// Loop through the lines
	for(int i = m_iCurrentLine; i <= m_iCurrentLine+MAX_LINES_PER_WINDOW; i++)
	{
		// Make sure its created
		if(m_bCreated[i])
		{
			// Copy the message
			strcpy(szMsg, m_szLineText[i]);
			// If line type is a chat then render the player name first
			if(m_LineType[i] == LINE_TYPE_CHAT)
			{
				char szName[17];
				sprintf(szName, "%s:", m_szNick[i]);
				m_pFont->GetFont()->DrawText(NULL, szName, -1, &NickRect, DT_CALCRECT|DT_LEFT, 0xFF000000);
				m_pFont->DrawText(szName, 0xFF000000, fX-1, fY);
				m_pFont->DrawText(szName, 0xFF000000, fX+1, fY);
				m_pFont->DrawText(szName, 0xFF000000, fX, fY-1);
				m_pFont->DrawText(szName, 0xFF000000, fX, fY+1);
				m_pFont->DrawText(szName, m_dNickColor[i], fX, fY);
				fY = (float)(46.0f+(NickRect.right - NickRect.left));
			}
			// Render the message
			m_pFont->DrawText(szMsg, 0xFF000000, fX-1, fY);
			m_pFont->DrawText(szMsg, 0xFF000000, fX+1, fY);
			m_pFont->DrawText(szMsg, 0xFF000000, fX, fY-1);
			m_pFont->DrawText(szMsg, 0xFF000000, fX, fY+1);
			m_pFont->DrawText(szMsg, m_dColor[i], fX, fY);
			// Increase the x position for the next one
			fX += 25.0f;
			fY = 40.0f;
		}
	}
}

void CChatBox::Up()
{
	if(m_iCurrentLine <= 0)
		return;

	m_iCurrentLine--;
}

void CChatBox::Down()
{
	if((m_iCurrentLine+MAX_LINES_PER_WINDOW) >= m_iLines || m_iLines <= MAX_LINES_PER_WINDOW)
		return;

	m_iCurrentLine++;
}

void CChatBox::Toggle()
{
	if(m_bEnabled)
		m_bEnabled = false;
	else
		m_bEnabled = true;
}

void CChatBox::OnLostDevice()
{
	m_pFont->GetFont()->OnLostDevice();
}

void CChatBox::OnResetDevice()
{
	m_pFont->GetFont()->OnResetDevice();
}



