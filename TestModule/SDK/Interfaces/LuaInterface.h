#ifndef LUAINTERFACE_H
#define LUAINTERFACE_H

#include "InterfaceUtils.h"

class CLuaInterface
{
	public:
		virtual int CallEvent(char *szEvent, char *szFormat, ...) = 0;

};

#endif