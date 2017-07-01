/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: BlipInfo.h
-- Project: Client
-- Author(s): m0niSx
-- Description: BlipInfo handler header file
=============================================================*/

#ifndef BLIPINFO_H
#define BLIPINFO_H

#include "VBlipInfo.h"

class CBlipInfo
{
	public:
		CBlipInfo(CVBlipInfo *pBlipInfo);
		~CBlipInfo();

		//////////////////////////////////////////////////////////////////////
		inline void SetHandler(CVBlipInfo *pBlipInfo)
		{
			// do we have a valid pointer ?
			if(pBlipInfo)
				// Set blip info pointer
				m_pBlipInfo = pBlipInfo;
		}
		inline CVBlipInfo *GetHandler() { return m_pBlipInfo; };

		//////////////////////////////////////////////////////////////////////
		bool IsBlipCreated() { return m_pBlipInfo == NULL ? false : m_pBlipInfo->bCreatedFlag; };
		unsigned int GetBlipAttachedEntityIndex() { return m_pBlipInfo == NULL ? INVALID_PLAYER_INDEX : m_pBlipInfo->uiEntityIndex; };
		CVector3 *GetBlipPosition() { return m_pBlipInfo == NULL ? &CVector3() : &m_pBlipInfo->vecPosition; };
		DWORD GetBlipColor() { return m_pBlipInfo == NULL ? 0 : m_pBlipInfo->dwColor; };
		void SetBlipColor(DWORD dwColor) { m_pBlipInfo == NULL ? dwColor = 0 : m_pBlipInfo->dwColor = dwColor; };
		float GetBlipScale() { return m_pBlipInfo == NULL ? 0.0f : m_pBlipInfo->fScale; };
		void SetBlipScale(float fScale) { m_pBlipInfo == NULL ? fScale = 0.0f : m_pBlipInfo->fScale = fScale; };
		int GetBlipAlpha() { return m_pBlipInfo == NULL ? 0 : m_pBlipInfo->iAlpha; };
		void SetBlipAlpha(int iAlpha) { m_pBlipInfo == NULL ? iAlpha = 0 : m_pBlipInfo->iAlpha = iAlpha; };
		eBlipSprite GetBlipSprite() { return m_pBlipInfo == NULL ? BLIP_PLAYER : m_pBlipInfo->sprite; };
		void SetBlipSprite(eBlipSprite sprite) { m_pBlipInfo == NULL ? sprite = BLIP_PLAYER : m_pBlipInfo->sprite = sprite; };


	private:
		CVBlipInfo		*m_pBlipInfo;
};

#endif