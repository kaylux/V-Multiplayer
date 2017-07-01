/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: NameTags.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Client nametags handler header file
=============================================================*/

#ifndef NAMETAGS_H
#define NAMETAGS_H

#include "Font.h"
#include <d3dx9.h>

class CNameTags
{
	public:
		CNameTags(IDirect3DDevice9 *pDevice);
		~CNameTags();

		///////////////////////////////////////////////////////////
		inline void Toggle(bool bToggle) { m_bEnabled = bToggle; };
		inline bool IsEnabled() { return m_bEnabled; };

		///////////////////////////////////////////////////////////
		inline void SetView(D3DXMATRIX matView) { m_matView = matView; };
		inline void SetProjection(D3DXMATRIX matProjection) { m_matProjection = matProjection; };

		///////////////////////////////////////////////////////////
		void Render();

		///////////////////////////////////////////////////////////
		void OnLostDevice();
		void OnRestDevice();

	private:
		bool						m_bEnabled;
		IDirect3DDevice9			*m_pDevice;
		CFont						*m_pFont;
		D3DXMATRIX					m_matView;
		D3DXMATRIX					m_matProjection;

};

#endif