/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Blip.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Blip class header file
=============================================================*/

#ifndef BLIP_H
#define BLIP_H

#include "BlipInfo.h"
#include <Common.h>

enum eBlipType
{
	BLIP_TYPE_VEHICLE = 1,
	BLIP_TYPE_PLAYER = 2,
	BLIP_TYPE_COORD = 4,
	BLIP_TYPE_OBJECT = 5,
	BLIP_TYPE_PICKUP = 6
};

class CBlip
{
	public:
		CBlip(eBlipType type);
		~CBlip();
		
		////////////////////////////////////////////////////////////////////////////
		void Create();
		void Destroy();

		////////////////////////////////////////////////////////////////////////////
		void SetBlipParam(unsigned int uiEntityIndex)
		{
			if(m_type == BLIP_TYPE_PLAYER || m_type == BLIP_TYPE_VEHICLE ||m_type == BLIP_TYPE_OBJECT || m_type == BLIP_TYPE_PICKUP)
				m_iEntityIndex = uiEntityIndex;
		};

		void SetBlipParam(CVector3 vecPosition)
		{
			if(m_type == BLIP_TYPE_COORD)
				m_vecPosition = vecPosition;
		};

		////////////////////////////////////////////////////////////////////////////
		inline void SetBlipInfo(CBlipInfo *pBlipInfo)
		{
			// do we have a valid pointer ?
			if(pBlipInfo)
				// Set blip ped pointer
				m_pBlipInfo = pBlipInfo;
		}
		inline CBlipInfo *GetBlipInfo() { return m_pBlipInfo; }; 




	private:
		unsigned int		m_uiBlipIndex;
		CBlipInfo			*m_pBlipInfo;
		eBlipType			m_type;
		int					m_iEntityIndex;
		CVector3			m_vecPosition;
		
};

#endif