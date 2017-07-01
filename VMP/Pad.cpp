/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Pad.cpp
-- Project: Client
-- Author(s): m0niSx
-- Description: Pad handler source file
=============================================================*/

#include "Main.h"

CPad::CPad(CVPad *pPad)
{
	// Set the pad pointer
	m_pPad = pPad;
}

CPad::~CPad()
{

}

bool CPad::IsControlJustPressed(ePadKeys pad)
{
	// Handle control check the way GTA IV handles it
	BYTE byteValue = m_pPad->pads[pad].byteCurrentValue ^ m_pPad->pads[pad].byteCurrentValueFlag;
	if(byteValue <= 127)
		return false;
	
	byteValue = m_pPad->pads[pad].byteLastValue ^ m_pPad->pads[pad].byteCurrentValueFlag;
	if(byteValue > 127)
		return false;	
	
	return true;
}
