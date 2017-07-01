/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VGTAVector.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game vector class header file
=============================================================*/

#ifndef VGTAVECTOR_H
#define VGTAVECTOR_H

#include <SharedUtility.h>

#pragma pack(push, 1)
class CVGTAVector
{
	public:
		float	fX;			// 0x0000 - 0x0004
		float	fY;			// 0x0004 - 0x0008
		float	fZ;			// 0x0008 - 0x000C
		float	fUnk;		// 0x000C - 0x0010
	
		CVGTAVector(CVector3 vecPoint)
		{
			fX = vecPoint.fX;
			fY = vecPoint.fY;
			fZ = vecPoint.fZ;
			fUnk = 0.0f;
		};


};
#pragma pack(pop)

#endif