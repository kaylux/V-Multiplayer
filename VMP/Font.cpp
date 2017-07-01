/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Font.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Client font source file
=============================================================*/

#include "Main.h"

CFont::CFont(IDirect3DDevice9 *pDevice, int iSize, char *szFontName, UINT wWeight)
{
	D3DXCreateFont(pDevice, iSize, 0, wWeight, 1, false, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, PROOF_QUALITY, DEFAULT_PITCH, szFontName, &m_pFont);
}

CFont::~CFont()
{
	SAFE_DELETE(m_pFont);
}

void CFont::DrawText(char *szText, D3DCOLOR dColor, float fX, float fY)
{
	RECT rect;
	rect.top = (int)fX;
	rect.left = (int)fY;
	rect.bottom = 2000;
	rect.right = 2000;
	m_pFont->DrawTextA(NULL, szText, -1, &rect, DT_NOCLIP, dColor);
}

