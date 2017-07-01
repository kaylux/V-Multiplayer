/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: Maths.h
-- Project: Shared
-- Author(s): m0niSx
-- Description: Maths functions header file
=============================================================*/

#ifndef MATHS_H
#define MATHS_H

#include "Common.h"
#include "SharedUtility.h"

class CMath
{
	public:
		static float GetDistanceBetween3DPoints(CVector3 vecPosition, CVector3 _vecPosition);
};

#endif