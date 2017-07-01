/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: GameGui.h
-- Project: Client
-- Author(s): m0niSx
-- Description: VMP client game GUI header file
=============================================================*/

#ifndef GAMEGUI_H
#define GAMEGUI_H

// CEGUI Includes
#include <CEGUI.h>
#include <CEGUIDirect3D9Renderer.h>
// DirectInput8 includes
#include <dinput.h>
// Include the SharedUtility
#include <SharedUtility.h>

#define STYLE_VMP "GWEN"

using namespace CEGUI;

// GUI Window types
enum eElementType
{
	ELEMENT_TYPE_WINDOW,
	ELEMENT_TYPE_BUTTON,
	ELEMENT_TYPE_EDITBOX,
	ELEMENT_TYPE_IMAGE,
	ELEMENT_TYPE_TEXT
};

class CGameGui
{
	public:
		CGameGui(IDirect3DDevice9 *pDevice);
		~CGameGui();

		///////////////////////////////////////////////////////////
		bool Initialize(HWND hWnd);

		///////////////////////////////////////////////////////////
		inline System				*GetSystem() { return m_pSystem; };
		inline WindowManager		*GetWindowManager() { return m_pWindowManager; };
		inline DefaultWindow		*GetDefaultWindow() { return m_pDefaultWindow; };
		inline MouseCursor			*GetMouseCursor() { return m_pCursor; };

		///////////////////////////////////////////////////////////
		template <typename T>
		T CreateElement(eElementType type, char *szElementName, Window *pSubWindow)
		{
			// Get the element name from type
			char szTypeName[32];
			GetElementNameFromType(type, szTypeName);
			// Set the element type name
			char szElementType[64];
			sprintf(szElementType, STYLE_VMP "/%s", szTypeName); // We use only WindowsLook for the moment
			// Create the element
			T element = static_cast<T>(m_pWindowManager->createWindow(szElementType, szElementName));
			// Add the new element to the sub window
			pSubWindow->addChildWindow(element);
			// Return the element instance
			return element;
		}
		///////////////////////////////////////////////////////////
		inline const char *GetEditBoxText(Editbox *pEditBox) { return pEditBox->getText().c_str() != 0 ? pEditBox->getText().c_str() : 0; };

		///////////////////////////////////////////////////////////
		inline bool IsCursorVisible() { return m_pCursor->isVisible() ;};
		void ToggleCursor(bool bToggle);

		///////////////////////////////////////////////////////////
		void HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		void ProcessCursor();
		void Render();

		///////////////////////////////////////////////////////////
		void OnLostDevice();
		void OnResetDevice();

	private:
		bool								m_bInitialized;
		IDirect3DDevice9					*m_pDevice;
		Direct3D9Renderer					*m_pRenderer;
		System								*m_pSystem;
		WindowManager						*m_pWindowManager;
		Scheme								*m_pScheme;
		MouseCursor							*m_pCursor;
		DefaultWindow						*m_pDefaultWindow;
		Font								*m_pDefaultFont;
		GeometryBuffer						*m_pTextDrawingGeometryBuffer;
		CVector2							m_vecCursorPosition;
		bool								m_bKeyPressed[3];
		IDirectInput8						*m_pInput;
		IDirectInputDevice8					*m_pInputDevice;

		void GetElementNameFromType(eElementType type, char *szName)
		{
			// Set the name depending on the type
			if(type == ELEMENT_TYPE_WINDOW)
				strcpy(szName, "FrameWindow");
			else if(type == ELEMENT_TYPE_BUTTON)
				strcpy(szName, "Button");
			else if(type == ELEMENT_TYPE_EDITBOX)
				strcpy(szName, "Editbox");
			else if(type == ELEMENT_TYPE_IMAGE)
				strcpy(szName, "StaticImage");
			else if(type == ELEMENT_TYPE_TEXT)
				strcpy(szName, "StaticText");
		}

};

#endif