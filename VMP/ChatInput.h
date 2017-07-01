/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: ChatInput.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Client chatinput header file
=============================================================*/

#ifndef CHATINPUT_H
#define CHATINPUT_H

#include "Font.h"

#define MAX_INPUT 128

class CChatInput
{
	public:
		CChatInput(IDirect3DDevice9 *pDevice);
		~CChatInput();

		////////////////////////////////////////////////
		void AddInput(char cInput);
		void DeleteInput();

		////////////////////////////////////////////////
		void Right();
		void Left();

		////////////////////////////////////////////////
		inline bool IsEnabled() { return m_bEnabled; };
		inline void Toggle();

		////////////////////////////////////////////////
		void Render();

		////////////////////////////////////////////////
		void HandleInput();

		////////////////////////////////////////////////
		void OnLostDevice();
		void OnResetDevice();

	private:
		IDirect3DDevice9			*m_pDevice;
		bool						m_bEnabled;
		BYTE						m_byteLength;
		BYTE						m_byteCharacter;
		char						m_szText[MAX_INPUT];
		CFont						*m_pSliceFont;
		CFont						*m_pFont;
		DWORD						m_dwLastTick;
		bool						m_bSlice;
};

#endif