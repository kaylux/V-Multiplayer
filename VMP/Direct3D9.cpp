/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Direct3D9.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Direct3D9 interface hook source file
=============================================================*/

#include "Main.h"

extern CGame		*pGame;

CIDirect3D9::CIDirect3D9(IDirect3D9 *pOriginal)
{
    m_pIDirect3D9 = pOriginal;
}

CIDirect3D9::~CIDirect3D9(void)
{
}

HRESULT __stdcall CIDirect3D9::QueryInterface(REFIID riid, void** ppvObj)
{
    *ppvObj = NULL;
	HRESULT hRes = m_pIDirect3D9->QueryInterface(riid, ppvObj); 
	if (hRes == NOERROR) 
	{
		*ppvObj = this;
	}
	return hRes;
}

ULONG __stdcall CIDirect3D9::AddRef(void)
{
    return(m_pIDirect3D9->AddRef());
}

ULONG __stdcall CIDirect3D9::Release(void)
{
	ULONG uCount = m_pIDirect3D9->Release();
	if(uCount == 0) 
  	    delete this; 

	return uCount;
}

HRESULT __stdcall CIDirect3D9::RegisterSoftwareDevice(void* pInitializeFunction)
{
    return(m_pIDirect3D9->RegisterSoftwareDevice(pInitializeFunction));
}

UINT __stdcall CIDirect3D9::GetAdapterCount(void)
{
    return(m_pIDirect3D9->GetAdapterCount());
}

HRESULT __stdcall CIDirect3D9::GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier)
{
    return(m_pIDirect3D9->GetAdapterIdentifier(Adapter,Flags,pIdentifier));
}

UINT __stdcall CIDirect3D9::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format)
{
    return(m_pIDirect3D9->GetAdapterModeCount(Adapter, Format));
}

HRESULT __stdcall CIDirect3D9::EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode)
{
    return(m_pIDirect3D9->EnumAdapterModes(Adapter,Format,Mode,pMode));
}

HRESULT __stdcall CIDirect3D9::GetAdapterDisplayMode( UINT Adapter,D3DDISPLAYMODE* pMode)
{
    return(m_pIDirect3D9->GetAdapterDisplayMode(Adapter,pMode));
}

HRESULT __stdcall CIDirect3D9::CheckDeviceType(UINT iAdapter,D3DDEVTYPE DevType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed)
{
    return(m_pIDirect3D9->CheckDeviceType(iAdapter,DevType,DisplayFormat,BackBufferFormat,bWindowed));
}

HRESULT __stdcall CIDirect3D9::CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat)
{
    return(m_pIDirect3D9->CheckDeviceFormat(Adapter,DeviceType,AdapterFormat,Usage,RType,CheckFormat));
}

HRESULT __stdcall CIDirect3D9::CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
{
    return(m_pIDirect3D9->CheckDeviceMultiSampleType(Adapter,DeviceType,SurfaceFormat,Windowed,MultiSampleType,pQualityLevels));
}

HRESULT __stdcall CIDirect3D9::CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat)
{
    return(m_pIDirect3D9->CheckDepthStencilMatch(Adapter,DeviceType,AdapterFormat,RenderTargetFormat,DepthStencilFormat));
}

HRESULT __stdcall CIDirect3D9::CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat)
{
    return(m_pIDirect3D9->CheckDeviceFormatConversion(Adapter,DeviceType,SourceFormat,TargetFormat));
}

HRESULT __stdcall CIDirect3D9::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps)
{
    return(m_pIDirect3D9->GetDeviceCaps(Adapter,DeviceType,pCaps));
}

HMONITOR __stdcall CIDirect3D9::GetAdapterMonitor(UINT Adapter)
{
    return(m_pIDirect3D9->GetAdapterMonitor(Adapter));
}

HRESULT __stdcall CIDirect3D9::CreateDevice(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface)
{
	// Create the real Direct3D9 device
	HRESULT hResult = m_pIDirect3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, 
		ppReturnedDeviceInterface);

	// Is device creation succeeded
	if(SUCCEEDED(hResult))
	{
		// Create our hook device
		CIDirect3DDevice9  *pD3Device = new CIDirect3DDevice9(this, *ppReturnedDeviceInterface);
		// Subclass the game window
		SubclassGameWindow(hFocusWindow);
		// Set the game HWND
		if(pGame)
			pGame->SetHWND(hFocusWindow);

		// Setup Direct3D9 classes
		if(pGame)
			pGame->SetupDevice(*ppReturnedDeviceInterface);

		// Set the returned device to use our hooked class
		*ppReturnedDeviceInterface = pD3Device;
	}
	return hResult; 
}