/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Pad.h
-- Project: Client
-- Author(s): m0niSx
-- Description: Pad handler header file
=============================================================*/

#ifndef PAD_H
#define PAD_H

#include "VPad.h"
#include "GameUtils.h"

class CPad
{
	public:
		CPad(CVPad *pPad);
		~CPad();

		////////////////////////////////////////////////
		inline CVPad *GetHandler() { return m_pPad; };

		////////////////////////////////////////////////
		bool IsControlJustPressed(ePadKeys pad);

	private:
		CVPad		*m_pPad;

};

#endif
