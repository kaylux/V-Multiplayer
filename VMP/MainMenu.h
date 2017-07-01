/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: MainMenu.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Main menu handler header file
=============================================================*/

#ifndef MAINMENU_H
#define MAINMENU_H

#include "GameGui.h"

class CMainMenu
{
	public:
		CMainMenu();
		~CMainMenu();

		///////////////////////////////////////////////////////////
		bool Initialize();

		bool OnConnectButtonClick(const EventArgs &args);

		///////////////////////////////////////////////////////////
		inline bool IsActive() { return m_bActive; };
		void Toggle(bool bToggle);

	private:
		bool					m_bInitialized;
		bool					m_bActive;
		// Background elements
		Imageset				*m_pBackgroundImage;
		Window					*m_pBackgroundElement;
		// Connect window elements (TODO: move this to its own class)
		Window					*m_pConnectWindow;
		Editbox					*m_pIpEditBox;
		Editbox					*m_pPortEditBox;
		Window					*m_pIpText;
		Window					*m_pPortText;
		PushButton				*m_pConnectButton;
};

#endif