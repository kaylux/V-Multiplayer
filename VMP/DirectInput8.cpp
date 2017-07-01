/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: DirectInput8.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: DirectInput8 interface hook source file
=============================================================*/

#include "Main.h"

CDirectInput8::CDirectInput8(IDirectInput8 * dinput)
{
	m_dinput = dinput;
}

HRESULT STDMETHODCALLTYPE CDirectInput8::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	return m_dinput->QueryInterface(riid, ppvObj);
}

ULONG STDMETHODCALLTYPE CDirectInput8::AddRef()
{
	return m_dinput->AddRef();
}

ULONG STDMETHODCALLTYPE CDirectInput8::Release()
{
	ULONG uRet = m_dinput->Release();

	// If the reference count is 0 delete ourselves
	if(uRet == 0)
		delete this;

	return uRet;
}

HRESULT STDMETHODCALLTYPE CDirectInput8::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICE8A * lplpDirectInputDevice, LPUNKNOWN pUknOuter)
{
	// Create the dinput device
	HRESULT hr = m_dinput->CreateDevice(rguid, lplpDirectInputDevice, pUknOuter);

	if(SUCCEEDED(hr))
		// Create the proxy device
		*lplpDirectInputDevice = new CDirectInputDevice8(this, *lplpDirectInputDevice, rguid);

	return hr;
}

HRESULT STDMETHODCALLTYPE CDirectInput8::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_dinput->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE CDirectInput8::GetDeviceStatus(REFGUID rguidInstance)
{
	return m_dinput->GetDeviceStatus(rguidInstance);
}

HRESULT STDMETHODCALLTYPE CDirectInput8::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return m_dinput->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT STDMETHODCALLTYPE CDirectInput8::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return m_dinput->Initialize(hinst, dwVersion);
}

HRESULT STDMETHODCALLTYPE CDirectInput8::FindDevice(REFGUID rguidClass, LPCSTR ptszName, LPGUID pguidInstance)
{
	return m_dinput->FindDevice(rguidClass, ptszName, pguidInstance);
}

HRESULT STDMETHODCALLTYPE CDirectInput8::EnumDevicesBySemantics(LPCSTR ptszUserName, LPDIACTIONFORMATA lpdiActionFormat, LPDIENUMDEVICESBYSEMANTICSCBA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return m_dinput->EnumDevicesBySemantics(ptszUserName, lpdiActionFormat, lpCallback, pvRef, dwFlags);
}

HRESULT STDMETHODCALLTYPE CDirectInput8::ConfigureDevices(LPDICONFIGUREDEVICESCALLBACK lpdiCallback, LPDICONFIGUREDEVICESPARAMSA lpdiCDParams, DWORD dwFlags, LPVOID pvRefData)
{
	return m_dinput->ConfigureDevices(lpdiCallback, lpdiCDParams, dwFlags, pvRefData);
}
