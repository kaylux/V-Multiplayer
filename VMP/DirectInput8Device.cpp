/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: DirectInput8Device.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: DirectInput8 interface hook source file
=============================================================*/

#include "Main.h"

extern CGame	*pGame;

CDirectInputDevice8::CDirectInputDevice8(IDirectInput8 * dinput, IDirectInputDevice8 * dinputdevice, GUID Type)
{
	m_pDI = dinput;
	m_pDIDevice = dinputdevice;
	m_Type = Type;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_pDIDevice->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE CDirectInputDevice8::AddRef()
{
	return m_pDIDevice->AddRef();
}

ULONG STDMETHODCALLTYPE CDirectInputDevice8::Release()
{
	ULONG uRet = m_pDIDevice->Release();

	// If the reference count is 0 delete ourselves
	if(uRet == 0)
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::GetCapabilities(LPDIDEVCAPS p0)
{
	return m_pDIDevice->GetCapabilities(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::EnumObjects(LPDIENUMDEVICEOBJECTSCALLBACKA p0, LPVOID p1, DWORD p2)
{
	return m_pDIDevice->EnumObjects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::GetProperty(REFGUID rguid, LPDIPROPHEADER p1)
{
	return m_pDIDevice->GetProperty(rguid, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::SetProperty(REFGUID rguid, LPCDIPROPHEADER p1)
{
	return m_pDIDevice->SetProperty(rguid, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::Acquire()
{
	return m_pDIDevice->Acquire();
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::Unacquire()
{
	return m_pDIDevice->Unacquire();
}

extern bool bUs;
char cOldReturn = 0;

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::GetDeviceState(DWORD p0, LPVOID p1)
{
	HRESULT hResult = m_pDIDevice->GetDeviceState(p0, p1);
	// Are we in the main menu
	if(pGame->GetGameState() == GAME_STATE_LOADING_SCREEN)
	{
		if(*(bool *)(pGame->GetBaseAddress() + 0x10C7F6F) == true)
		{
			// TODO: ofc move this thing to a nice and clean place (hook maybe)
			//pGame->SetupNetwork("127.0.0.1", 3333);
			// Set the game state
			pGame->SetGameState(GAME_STATE_MAIN_MENU);
			// Initialize GUI
			pGame->InitializeGUI();
			// Toggle main menu on
			pGame->GetMainMenu()->Toggle(true);
		}
	}
	// Are we processing the menu
	if(pGame->GetGameState() == GAME_STATE_MAIN_MENU)
	{
		// Dont process keys
		if(m_Type == GUID_SysKeyboard)
		{
			memset(p1, 0, p0);
		}
		// Dont process mouse input
		if(m_Type == GUID_SysMouse && !bUs)
			memset(p1, 0, p0);
	}
	// Are we skipping the main menu ?GAME_STATE_MAIN_MENU
	if(pGame->GetGameState() == GAME_STATE_LOADING_GAME || pGame->GetGameState() == GAME_STATE_LOADING_SCREEN)
	{
		if(m_Type == GUID_SysKeyboard)
		{
			// Make a fake RETURN key press
			char *szBuf = (char *)p1;
			cOldReturn = !cOldReturn;
			szBuf[DIK_RETURN] = cOldReturn;
		}
	}
	return hResult;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::GetDeviceData(DWORD p0, LPDIDEVICEOBJECTDATA p1, LPDWORD p2, DWORD p3)
{
	HRESULT hResult = m_pDIDevice->GetDeviceData(p0, p1, p2, p3);
	return hResult;
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::SetDataFormat(LPCDIDATAFORMAT p0)
{
	return m_pDIDevice->SetDataFormat(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::SetEventNotification(HANDLE p0)
{
	return m_pDIDevice->SetEventNotification(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::SetCooperativeLevel(HWND p0, DWORD p1)
{
	return m_pDIDevice->SetCooperativeLevel(p0, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::GetObjectInfo(LPDIDEVICEOBJECTINSTANCEA p0, DWORD p1, DWORD p2)
{
	return m_pDIDevice->GetObjectInfo(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::GetDeviceInfo(LPDIDEVICEINSTANCEA p0)
{
	return m_pDIDevice->GetDeviceInfo(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::RunControlPanel(HWND p0, DWORD p1)
{
	return m_pDIDevice->RunControlPanel(p0, p1);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::Initialize(HINSTANCE p0, DWORD p1, REFGUID rguid)
{
	return m_pDIDevice->Initialize(p0, p1, rguid);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::CreateEffect(REFGUID rguid, LPCDIEFFECT p1, LPDIRECTINPUTEFFECT * p2, LPUNKNOWN p3)
{
	return m_pDIDevice->CreateEffect(rguid, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::EnumEffects(LPDIENUMEFFECTSCALLBACKA p0, LPVOID p1, DWORD p2)
{
	return m_pDIDevice->EnumEffects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::GetEffectInfo(LPDIEFFECTINFOA p0, REFGUID rguid)
{
	return m_pDIDevice->GetEffectInfo(p0, rguid);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::GetForceFeedbackState(LPDWORD p0)
{
	return m_pDIDevice->GetForceFeedbackState(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::SendForceFeedbackCommand(DWORD p0)
{
	return m_pDIDevice->SendForceFeedbackCommand(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::EnumCreatedEffectObjects(LPDIENUMCREATEDEFFECTOBJECTSCALLBACK p0, LPVOID p1, DWORD p2)
{
	return m_pDIDevice->EnumCreatedEffectObjects(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::Escape(LPDIEFFESCAPE p0)
{
	return m_pDIDevice->Escape(p0);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::Poll()
{
	return m_pDIDevice->Poll();
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::SendDeviceData(DWORD p0, LPCDIDEVICEOBJECTDATA p1, LPDWORD p2, DWORD p3)
{
	return m_pDIDevice->SendDeviceData(p0, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::EnumEffectsInFile(LPCSTR p0, LPDIENUMEFFECTSINFILECALLBACK p1, LPVOID p2, DWORD p3)
{
	return m_pDIDevice->EnumEffectsInFile(p0, p1, p2, p3);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::WriteEffectToFile(LPCSTR p0, DWORD p2, LPDIFILEEFFECT p3, DWORD p4)
{
	return m_pDIDevice->WriteEffectToFile(p0, p2, p3, p4);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::BuildActionMap(LPDIACTIONFORMATA p0, LPCSTR p1, DWORD p2)
{
	return m_pDIDevice->BuildActionMap(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::SetActionMap(LPDIACTIONFORMATA p0, LPCSTR p1, DWORD p2)
{
	return m_pDIDevice->SetActionMap(p0, p1, p2);
}

HRESULT STDMETHODCALLTYPE CDirectInputDevice8::GetImageInfo(LPDIDEVICEIMAGEINFOHEADERA p0)
{
	return m_pDIDevice->GetImageInfo(p0);
}
