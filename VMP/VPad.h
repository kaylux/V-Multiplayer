/* =========================================================
		  V:Multiplayer - http://www.vmultiplayer.com

-- File: VPad.h
-- Project: Client
-- Author(s): m0niSx
-- Description: V Game pad handler header file
=============================================================*/

#ifndef VPAD_H
#define VPAD_H

#include <SharedUtility.h>

#pragma pack(push, 1)
class CVPads
{
	public:
		PAD(pad0, 4);					// 0x0000 - 0x0004
		BYTE	byteCurrentValueFlag;	// 0x0004 - 0x0005 (xor byteCurrentValue >= 128 then xor byteLastValue >= 128)
		PAD(pad1, 1);					// 0x0005 - 0x0006
		BYTE	byteCurrentValue;		// 0x0006 - 0x0007
		BYTE	byteLastValue;			// 0x0007 - 0x0008
		PAD(pad2, 8);					// 0x0008 - 0x0016
};
#pragma pack(pop)

#pragma pack(push, 1)
class CVPad
{
	public:
		PAD(pad0, 9880);				// 0x0000 - 0x2698
		CVPads		pads[188];			// 0x2698 - 0x3248
		PAD(pad1, 2108);				// 0x3248 - 0x3A84
};
#pragma pack(pop)

#endif