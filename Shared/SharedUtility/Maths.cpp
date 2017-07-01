/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Maths.cpp
-- Project: Shared
-- Author(s): m0niSx
-- Description: Maths functions source file
=============================================================*/

#include <math.h>
#include "Maths.h"

float CMath::GetDistanceBetween3DPoints(CVector3 vecPosition, CVector3 _vecPosition)
{
	// Get the distance between the two vectors
	float fSX = (_vecPosition.fX - vecPosition.fX) * (_vecPosition.fX - vecPosition.fX);
	float fSY = (_vecPosition.fY - vecPosition.fY) * (_vecPosition.fY - vecPosition.fY);
	float fSZ = (_vecPosition.fZ - vecPosition.fZ) * (_vecPosition.fZ - vecPosition.fZ);
	return ((float)sqrt(fSX + fSY + fSZ));	
}
