/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: GameGui.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: VMP client game GUI source file
=============================================================*/

#include "Main.h"

CGameGui::CGameGui(IDirect3DDevice9 *pDevice)
{
	// Save the d3d9 device pointer 
	m_pDevice = pDevice; 
	// Reset pointers
	m_pSystem = NULL;
	m_pRenderer = NULL;
	m_pWindowManager = NULL;
	m_pScheme = NULL;
	m_pCursor = NULL;
	m_pDefaultWindow = NULL;
	// Reset the cursor position vector
	memset(&m_vecCursorPosition, 0, sizeof(CVector2));
	// Reset the cursor click
	for(BYTE i = 0; i < 3; i++)
		m_bKeyPressed[i] = false;

	// Mark as not initialized
	m_bInitialized = false;
}

CGameGui::~CGameGui()
{
	// Make sure we are intialized before deleting anything
	if(m_bInitialized)
	{
		// Destroy all the windows
		m_pWindowManager->destroyAllWindows();
		// Delete the cursor instance
		SAFE_DELETE(m_pCursor);
		// Delete the scheme instance
		SAFE_DELETE(m_pScheme);
		// Delete the geometry buffer instance
		SAFE_DELETE(m_pTextDrawingGeometryBuffer);
		// Delete the window manager instance
		SAFE_DELETE(m_pWindowManager);
		// Delete the renderer instance
		m_pRenderer->destroy(*m_pRenderer);
		// Delete the system instance
		m_pSystem->destroy();
	}
}

bool CGameGui::Initialize(HWND hWnd)
{
	// Make sure we are not initialized yet
	if(m_bInitialized)
		return false;

	// Create the renderer instance
	m_pRenderer = &Direct3D9Renderer::create(m_pDevice);
	// Create the cegui system instance
	m_pSystem = &System::create(*m_pRenderer, 0, 0, 0, 0, "", "VMP/CEGUI/CEGUI_Log.txt");
	// Make sure the system and the rendered instances are created
	if(!m_pRenderer || !m_pSystem)
		return false;

	// Get the window manager instance
	m_pWindowManager = WindowManager::getSingletonPtr();
	// Get the resource provider instance
	DefaultResourceProvider *pResourceProvider = static_cast<DefaultResourceProvider *>(CEGUI::System::getSingleton().getResourceProvider());
	// Set resource group directorys
	pResourceProvider->setResourceGroupDirectory("schemes", "VMP/CEGUI/schemes/");
	pResourceProvider->setResourceGroupDirectory("imagesets", "VMP/CEGUI/imagesets/");
	pResourceProvider->setResourceGroupDirectory("fonts", "VMP/CEGUI/fonts/");
	pResourceProvider->setResourceGroupDirectory("layouts", "VMP/CEGUI/layouts/");
	pResourceProvider->setResourceGroupDirectory("looknfeels", "VMP/CEGUI/looknfeel/");
	pResourceProvider->setResourceGroupDirectory("schemas", "VMP/CEGUI/xml_schemas/");
	// Set the default resource groups to be used
	Imageset::setDefaultResourceGroup("imagesets");
	Font::setDefaultResourceGroup("fonts");
	Scheme::setDefaultResourceGroup("schemes");
	WidgetLookManager::setDefaultResourceGroup("looknfeels");
	m_pWindowManager->setDefaultResourceGroup("layouts");
	XMLParser *pParser = m_pSystem->getXMLParser();
	if(pParser->isPropertyPresent("SchemaDefaultResourceGroup"))
		pParser->setProperty("SchemaDefaultResourceGroup", "schemas");

	// Clear the default rendering root
	m_pRenderer->getDefaultRenderingRoot().clearGeometry(RQ_OVERLAY);
	// Specify the logging level (Informative)
	Logger::getSingleton().setLoggingLevel(Informative);
	// Create the scheme instance
	m_pScheme = &SchemeManager::getSingleton().create("GWEN.scheme");
	// Set the default mouse arrow
	m_pSystem->setDefaultMouseCursor(STYLE_VMP, "MouseArrow");
	// Create the cursor instance
	m_pCursor = MouseCursor::getSingletonPtr();
	// Create the default window
	m_pDefaultWindow = (DefaultWindow *)m_pWindowManager->createWindow("DefaultWindow", "defwin");
	m_pDefaultWindow->setSize(UVector2(UDim(1, 0), UDim(1, 0)));
	//GlobalEventSet::getSingletonPtr()->subscribeEvent(Window::EventNamespace + "/" + Window::EventKeyDown, Event::Subscriber(&CGameGui::OnGUIKeyDown, this));
	// Set the GUI default window instance
	m_pSystem->setGUISheet(m_pDefaultWindow);
	// Create the default font instance
	m_pDefaultFont = &FontManager::getSingleton().createFreeTypeFont("Tahoma", 8, true, "tahoma.ttf");
	// Set the GUI default font
	m_pSystem->setDefaultFont(m_pDefaultFont);
	// Hide the mouse
	m_pCursor->setVisible(false);
	// Create the geometry buffer instance 
	m_pTextDrawingGeometryBuffer = &m_pRenderer->createGeometryBuffer();
	m_pTextDrawingGeometryBuffer->setClippingRegion(Rect(Vector2(0, 0), m_pRenderer->getDisplaySize()));
	// Create the DirectInput8 instance
	if(FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8A, (LPVOID *)&m_pInput, NULL)))
		return false;

	// Create the DirectInput8 device instance
	if(FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pInputDevice, NULL)))
		return false;

	// Indicate that the DirectInput8 device is a mouse
	if(FAILED(m_pInputDevice->SetDataFormat(&c_dfDIMouse2)))
		return false;

	// Set the input DirectInput8 to non exclusive
	if(FAILED(m_pInputDevice->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
		return false;

	// Acquire the DirectInput8 device
	if(FAILED(m_pInputDevice->Acquire()))
		return false;

	// Mark as initialized
	m_bInitialized = true;
	return true;
}

void CGameGui::ToggleCursor(bool bToggle)
{
	// Make sure we are initialized
	if(!m_bInitialized)
		return;

	if(bToggle && !IsCursorVisible())
		m_pCursor->show();
	else if(IsCursorVisible())
		m_pCursor->hide();
}

void CGameGui::Render()
{
	// Make sure we are initialized
	if(m_bInitialized)
	{
		// Create the d3d9 state block
		IDirect3DStateBlock9 *pDeviceState = NULL;
		m_pDevice->CreateStateBlock(D3DSBT_ALL, &pDeviceState);
		// Render the GUI
		m_pSystem->renderGUI();
		// Apply and release the state blocks
		if(pDeviceState)
		{
			pDeviceState->Apply();
			pDeviceState->Release();
		}	
		// Process the cursor
		ProcessCursor();
	}
}

bool bUs = false;

void CGameGui::ProcessCursor()
{
	// If we have lost the device
	DIMOUSESTATE2 CursorState;
	bUs = true;
	if(m_pInputDevice->GetDeviceState(sizeof(CursorState), (LPVOID)&CursorState) == DIERR_INPUTLOST)
	{
		// Re-acquire it if we lost
		if(FAILED(m_pInputDevice->Acquire()))
			return;
	}
	bUs=false;
	// Add the new position coords to the cursor position
	m_vecCursorPosition.fX += CursorState.lX;
	m_vecCursorPosition.fY += CursorState.lY;
	// Dont let the mouse get out of the screen
	if(m_vecCursorPosition.fX < 0)
		m_vecCursorPosition.fX = 0;
	else if(m_vecCursorPosition.fX > m_pRenderer->getDisplaySize().d_width)
		m_vecCursorPosition.fX = m_pRenderer->getDisplaySize().d_width;

	if(m_vecCursorPosition.fY < 0)
		m_vecCursorPosition.fY = 0;
	else if(m_vecCursorPosition.fY > m_pRenderer->getDisplaySize().d_height)
		m_vecCursorPosition.fY = m_pRenderer->getDisplaySize().d_height;

	// Set the new cursor position
	m_pSystem->injectMousePosition(m_vecCursorPosition.fX, m_vecCursorPosition.fY);
	// Set the mouse wheel change
	if(CursorState.lZ != 0)
		m_pSystem->injectMouseWheelChange((float)CursorState.lZ);

	// Loop through the mouse keys (right, left, center)
	for(BYTE i = 0; i < 3; i++)
	{
		// Is the key pressed ?
		if(CursorState.rgbButtons[i] & 0x80)
		{
			// Is the key is not been pressed yet ?
			if(!m_bKeyPressed[i])
				// Indicate that the key has been pressed
				m_bKeyPressed[i] = true;
			else
				// Handle the down mouse click
				m_pSystem->injectMouseButtonDown((MouseButton)i);
		}
		else
		{
			// Is the key released
			if(m_bKeyPressed[i])
			{
				// Handle the up mouse click
				m_pSystem->injectMouseButtonUp((MouseButton)i);
				// Indicate that the key has been released
				m_bKeyPressed[i] = false;
			}
		}
	}
}

// TODO: Move this to shomewhere else (probably to SharedUtility or add it to the current class)
DWORD GetKeyDIK(WPARAM wParam)
{
	switch(wParam)
	{
	case 0x41: return DIK_A;               // Control + A (Select All)
	case 0x43: return DIK_C;               // Control + C (Copy)
	case 0x58: return DIK_X;               // Control + X (Cut)
	case 0x56: return DIK_V;               // Control + V (Paste)
	case VK_TAB: return DIK_TAB;           // Tab
	case VK_HOME: return DIK_HOME;         // Home
	case VK_END: return DIK_END;           // End
	case VK_INSERT: return DIK_INSERT;     // Insert
	case VK_DELETE: return DIK_DELETE;     // Delete
	case VK_UP: return DIK_UP;             // Arrow Up
	case VK_DOWN: return DIK_DOWN;         // Arrow Down
	case VK_LEFT: return DIK_LEFT;         // Arrow Left
	case VK_RIGHT: return DIK_RIGHT;       // Arrow Right
	case VK_SHIFT: return DIK_LSHIFT;      // Shift
	case VK_LSHIFT: return DIK_LSHIFT;     // Left Shift
	case VK_RSHIFT: return DIK_RSHIFT;     // Right Shift
	case VK_BACK: return DIK_BACK;         // Backspace
	case VK_RETURN: return DIK_RETURN;     // Enter
	case VK_CONTROL: return DIK_LCONTROL;  // Control
	case VK_LCONTROL: return DIK_LCONTROL; // Left Control
	case VK_RCONTROL: return DIK_RCONTROL; // Right Control
	}

	return 0;
}

void CGameGui::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// Make sure we are initialized
	if(!m_bInitialized)
		return;

	// Handle the message
	switch(uMsg)
	{
		case WM_CHAR:
			// Add the input to the GUI editboxs
			m_pSystem->injectChar((CEGUI::utf32)wParam);
			break;

		case WM_KEYDOWN:
		{
			// Get the DIK key code
			DWORD dwKey = GetKeyDIK(wParam);
			// Send the down key message
			m_pSystem->injectKeyDown(dwKey);
			break;
		}

		case WM_KEYUP:
		{
			// Get the DIK key code
			DWORD dwKey = GetKeyDIK(wParam);
			// Send the up key message
			m_pSystem->injectKeyUp(dwKey);
			break;
		}
	}
}

void CGameGui::OnLostDevice()
{
	// Make sure we are initialized
	if(m_bInitialized)
		m_pRenderer->preD3DReset();
}

void CGameGui::OnResetDevice()
{
	// Make sure we are initialized
	if(m_bInitialized)
		m_pRenderer->postD3DReset();
}