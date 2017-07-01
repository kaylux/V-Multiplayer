/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: MainMenu.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Main menu handler source file
=============================================================*/

#include "Main.h"

extern CGame	*pGame;

CMainMenu::CMainMenu()
{
	// Mark as not initialized
	m_bInitialized = false;
	// Mark not active
	m_bActive = false;
}

CMainMenu::~CMainMenu()
{

}

bool CMainMenu::Initialize()
{
	// Make sure we are not initialized yet
	if(m_bInitialized)
		return false;

	// Create the background image
	/*m_pBackgroundImage = &ImagesetManager::getSingleton().createFromImageFile("menu_logo", "background.png", "imagesets");
	// Create the image element
	m_pBackgroundElement = pGame->GetGameGui()->CreateElement<Window *>(ELEMENT_TYPE_IMAGE, "BackgroundImage", 
		pGame->GetGameGui()->GetSystem()->getGUISheet());

	// Set the background properties
	m_pBackgroundElement->setPosition(UVector2(UDim(0.0f, 0.0f), UDim(0.0f, 0.0f)));
	m_pBackgroundElement->setSize(UVector2(UDim(1.0f, 0.0f), UDim(1.0f, 0.0f)));
	m_pBackgroundElement->setProperty("Image", "set:menu_logo image:full_image");
	m_pBackgroundElement->setProperty("FrameEnabled", "false");
	m_pBackgroundElement->setProperty("BackgroundEnabled", "false");*/
	// Create the connect window
	m_pConnectWindow = pGame->GetGameGui()->CreateElement<Window *>(ELEMENT_TYPE_WINDOW, "ConnectWindow", pGame->GetGameGui()->GetSystem()->getGUISheet());
	// Set connect windw properties		
	m_pConnectWindow->setProperty("Text", "Quick Connect");
	m_pConnectWindow->setProperty("AlwaysOnTop", "True");
	m_pConnectWindow->setProperty("TitlebarFont", "Batang-10");
	m_pConnectWindow->setProperty("TitlebarEnabled", "True");
	m_pConnectWindow->setProperty("UnifiedAreaRect", "{{0.4675,0},{0.168165,0},{0.718125,0},{0.418165,0}}");
	// Create the IP & Port EditBoxs
	m_pIpEditBox = pGame->GetGameGui()->CreateElement<Editbox *>(ELEMENT_TYPE_EDITBOX, "ConnectWindow/IPEditBox", m_pConnectWindow);
	m_pPortEditBox = pGame->GetGameGui()->CreateElement<Editbox *>(ELEMENT_TYPE_EDITBOX, "ConnectWindow/PortEditBox", m_pConnectWindow);
	// Set editboxs properties
	m_pIpEditBox->setProperty("AlwaysOnTop", "True");
	m_pIpEditBox->setProperty("UnifiedAreaRect", "{{0.175,0},{0.155431,0},{0.73,0},{0.308052,0}}");
	m_pPortEditBox->setProperty("AlwaysOnTop", "True");
	m_pPortEditBox->setProperty("UnifiedAreaRect", "{{0.1825,0},{0.361049,0},{0.5125,0},{0.521161,0}}");
	// Create IP & Port Static Texts
	m_pIpText = pGame->GetGameGui()->CreateElement<Window *>(ELEMENT_TYPE_TEXT, "ConnectWindow/IPText", m_pConnectWindow);
	m_pPortText = pGame->GetGameGui()->CreateElement<Window *>(ELEMENT_TYPE_TEXT, "ConnectWindow/PortText", m_pConnectWindow);
	// Set IP text properties
	m_pIpText->setProperty("Text", "IP:");
	m_pIpText->setProperty("AlwaysOnTop", "True");
	m_pIpText->setProperty("HorzExtent", "33");
	//m_pIpText->setProperty("VertExtent", "33");
	m_pIpText->setProperty("FrameEnabled", "False");
	m_pIpText->setProperty("BackgroundEnabled", "False");
	m_pIpText->setProperty("UnifiedAreaRect", "{{0.035,0},{0.150187,0},{0.175,0},{0.299064,0}}");
	// Set Port text properties
	m_pPortText->setProperty("Text", "Port:");
	m_pPortText->setProperty("AlwaysOnTop", "True");
	m_pPortText->setProperty("HorzExtent", "61");
	//m_pPortText->setProperty("VertExtent", "33");
	m_pPortText->setProperty("FrameEnabled", "False");
	m_pPortText->setProperty("BackgroundEnabled", "False");
	m_pPortText->setProperty("UnifiedAreaRect", "{{0.0149999,0},{0.302622,0},{0.265,0},{0.552622,0}}");
	// Create the connect button
	m_pConnectButton = pGame->GetGameGui()->CreateElement<PushButton *>(ELEMENT_TYPE_BUTTON, "ConnectWindow/ConnectButton", m_pConnectWindow);
	// Set connect button properties
	m_pConnectButton->setProperty("Text", "Connect");
	m_pConnectButton->setProperty("AlwaysOnTop", "True");
	m_pConnectButton->setProperty("UnifiedAreaRect", "{{0.3225,0},{0.699625,0},{0.655,0},{0.900936,0}}");
	// Set the connect button event
	m_pConnectButton->subscribeEvent(PushButton::EventClicked, Event::Subscriber(&CMainMenu::OnConnectButtonClick, this));
	// Hide the windows
	//m_pBackgroundElement->hide();
	m_pConnectWindow->hide();
	// Mark as initialized
	m_bInitialized = true;
	return true;
}

bool bSkipMenu = false;

bool CMainMenu::OnConnectButtonClick(const EventArgs &args)
{
	// Get the IP & Port
	const char *szIP, *szPort = NULL;
	szIP = pGame->GetGameGui()->GetEditBoxText(m_pIpEditBox);
	szPort = pGame->GetGameGui()->GetEditBoxText(m_pPortEditBox);
	// Make sure the strings are valid
	if(!szIP || !szPort)
		return false;

	// Convert the port string to integer
	int iPort = atoi(szPort);
	// Make sure we have a valid integer
	if(iPort <= 0)
		return false;

	// Set the network IP & Port
	pGame->SetupNetwork((char *)szIP, iPort);
	// Hide the main menu
	Toggle(false);
	// Skip the main menu
	// Set the game state to loading game
	pGame->SetGameState(GAME_STATE_LOADING_GAME); // TODO: Yes, change that mesy shit
	return true;
}

void CMainMenu::Toggle(bool bToggle)
{
	// Make sure we are initialized
	if(!m_bInitialized)
		return;

	// Show the windows if we are enabling
	if(bToggle && !m_bActive)
	{
		//m_pBackgroundElement->show();
		m_pConnectWindow->show();
		// Show the cursor
		pGame->GetGameGui()->ToggleCursor(true);
		// Mark active
		m_bActive = true;
	}
	else if(m_bActive)
	{
		// Hide the windows if we are disabling
		//m_pBackgroundElement->hide();
		m_pConnectWindow->hide();
		// Hide the cursor
		pGame->GetGameGui()->ToggleCursor(false);
		// Mark not active
		m_bActive = false;
	}
}