/*
* 	ILuaInterface.cpp - Regan Russell
*
* 	The Lua interface is a wrapper for handling integration of
* 	the Lua scripting language with native C++ functions and other
*	applicable interfaces.
*/

#include "kopengi.h"

ILuaInterface::ILuaInterface()
{
	m_Lua = lua_open();
	luaL_openlibs(m_Lua);

	static const luaL_Reg regFuncs[] = {
		{"log", Log},
		{NULL, NULL}
	};

	lua_getglobal(m_Lua, "_G");
	luaL_register(m_Lua, NULL, regFuncs);
	lua_pop(m_Lua, 1);

	log(LOG_TYPE_DEFAULT, "Lua interface successfully initialized!");
}

ILuaInterface::~ILuaInterface()
{
	lua_close(m_Lua);
}

void ILuaInterface::LoadScript(std::string filepath)
{
	int status = luaL_loadfile(m_Lua, filepath.c_str());
	if (status == 0)
	{
		log(LOG_TYPE_DEFAULT, "Running script " + filepath + " ..");
		status = lua_pcall(m_Lua, 0, LUA_MULTRET, 0);
	}

	// Output errors
	if (status != 0)
	{
		log(LOG_TYPE_SCRIPT, "ERROR: " + std::string(lua_tostring(m_Lua, -1)));
		lua_pop(m_Lua, 1);
	}
}

int Log(lua_State* lua)
{
	int argc = lua_gettop(lua);
	std::stringstream msg;

	lua_getglobal(lua, "tostring");
	for (unsigned int i = 1; i <= argc; i++)
	{
		const char* arg;
		lua_pushvalue(lua, -1);
		lua_pushvalue(lua, i);
		lua_call(lua, 1, 1);
		arg = lua_tostring(lua, -1);

		if (arg == NULL)
		{
			return luaL_error(lua, "Values passed to Log must be convertable to string!");
		}
		
		if (i > 1)
		{
			msg << "\t";
		}

		msg << arg;
		lua_pop(lua, 1);
	}

	log(LOG_TYPE_SCRIPT, msg.str());
	return 0;
}
