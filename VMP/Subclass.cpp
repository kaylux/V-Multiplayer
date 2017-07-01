/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Subclass.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Client window subclass source file
=============================================================*/

#include "Main.h"

WNDPROC		hOldProc;
LRESULT		APIENTRY NewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void HandleUpKeys(DWORD dwKey);
void HandleDownKeys(DWORD dwKey);

extern CChatInput		*pChatInput;
extern CChatBox			*pChatBox;
extern CGame			*pGame;

bool bInit = false;

void SubclassGameWindow(HWND hGameWindow)
{
	// Set window text
	SetWindowText(hGameWindow, "V:MP v" VERSION);
	if(hGameWindow) 
	{
		// Get the window old process
		hOldProc = (WNDPROC)GetWindowLong(hGameWindow, GWL_WNDPROC);
		// Set the new process callback
		SetWindowLong(hGameWindow, GWL_WNDPROC, (LONG)NewWndProc);
	}
}

LRESULT APIENTRY NewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 	
	// Handle the GUI messages
	if(pGame->GetGameGui())
		pGame->GetGameGui()->HandleMessage(uMsg, wParam, lParam);

	switch(uMsg) 
	{
		case WM_KEYUP:
			HandleUpKeys((DWORD)wParam);
			break;

		case WM_KEYDOWN:
			HandleDownKeys((DWORD)wParam);
			break;

		case WM_CHAR:
			if(pChatInput && pChatInput->IsEnabled())
				pChatInput->AddInput((char)wParam);

			break;
	}
	return CallWindowProc(hOldProc,hwnd,uMsg,wParam,lParam);
}

void HandleUpKeys(DWORD dwKey)
{
	switch(dwKey)
	{
		case VK_F7:
			if(pChatInput)
				pChatInput->Toggle();

			break;

		case VK_RETURN:
			if(pChatInput)
				pChatInput->HandleInput();

			break;

		case VK_LEFT:
			if(pChatInput)
				pChatInput->Left();

			break;

		case VK_RIGHT:
			if(pChatInput)
				pChatInput->Right();

			break;

		case VK_NEXT:
			if(pChatBox)
				pChatBox->Up();

			break;

		case VK_PRIOR:
			if(pChatBox)
				pChatBox->Down();

			break;
	}
}

void HandleDownKeys(DWORD dwKey)
{
	switch(dwKey)
	{
		case VK_BACK:
			pChatInput->DeleteInput();
			break;
	}
}