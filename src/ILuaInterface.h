/*
* 	ILuaInterface.h - Regan Russell
*
* 	The Lua interface is a wrapper for handling integration of
* 	the Lua scripting language with native C++ functions and other
*	applicable interfaces.
*/

#ifndef _ILUAINTERFACE_H_
#define _ILUAINTERFACE_H_

class ILuaInterface
{
public:
	ILuaInterface();
	~ILuaInterface();

	void LoadScript(std::string filepath);
private:
	lua_State* m_Lua;
};

int Log(lua_State* lua);

#endif
