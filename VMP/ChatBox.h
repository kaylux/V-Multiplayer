/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ChatBox.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Client chatbox header file
=============================================================*/

#ifndef CHATBOX_H
#define CHATBOX_H

#include "Font.h"

#define MAX_MESSAGE_LENGTH 128
#define MAX_LINES_PER_WINDOW 10
#define MAX_LINES 100

enum eLineType
{
	LINE_TYPE_INFO,
	LINE_TYPE_DEBUG,
	LINE_TYPE_CHAT
};

class CChatBox
{
	public:
		CChatBox(IDirect3DDevice9 *pDevice);
		~CChatBox();

		void AddMessage(eLineType LineType, char *szPlayerName, D3DCOLOR dPlayerColor, D3DCOLOR dColor, char *szText, ...);

		void Render();

		void Up();
		void Down();

		void Toggle();
		bool IsEnabled() { return m_bEnabled; };

		void OnLostDevice();
		void OnResetDevice();

	private:
		IDirect3DDevice9	*m_pDevice;
		CFont				*m_pFont;
		char				m_szLineText[MAX_LINES][MAX_MESSAGE_LENGTH];
		char				m_szNick[MAX_LINES][16];
		D3DCOLOR			m_dNickColor[MAX_LINES];
		D3DCOLOR			m_dColor[MAX_LINES];
		bool				m_bCreated[MAX_LINES];
		eLineType			m_LineType[MAX_LINES];
		int					m_iCurrentLine;
		int					m_iLines;	
		bool				m_bEnabled;

};

#endif