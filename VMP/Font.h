/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Font.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Client font header file
=============================================================*/

#ifndef FONT_H
#define FONT_H

#include <d3dx9.h>

class CFont
{
	public:
		CFont(IDirect3DDevice9 *pDevice, int iSize, char *szFontName, UINT wWeight);
		~CFont();

		void DrawText(char *szText, D3DCOLOR dColor, float fX, float fY);
		ID3DXFont *GetFont() { return m_pFont; };

	private:
		ID3DXFont		*m_pFont;
};

#endif
