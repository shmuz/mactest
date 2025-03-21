#include <stdio.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "header.hpp"
#include "farplug-wide.h"
#include "lf_luafar.h"

const char FAR_PLUGINDATA[]    = "far.plugindata";

PluginStartupInfo PSInfo; // DON'T ever use fields ModuleName and ModuleNumber of PSInfo
                          // because they contain data of the 1-st loaded LuaFAR plugin.
                          // Instead, get them via GetPluginData(L).

SHAREDSYMBOL int libfunc(int arg)
{
  printf("libfunc() called\n");
  appfunc();
  return 0;
}

// Initialize the interpreter
int LF_LuaOpen (const struct PluginStartupInfo *aInfo, TPluginData* aPlugData, lua_CFunction aOpenLibs)
{
	if (PSInfo.StructSize == 0) {
		if (aInfo->StructSize < sizeof(*aInfo)) {
			return 0; // Far is too old
		}
		PSInfo = *aInfo;
		PSInfo.ModuleName = NULL;
		PSInfo.ModuleNumber = 0;
	}

	// create Lua State
	lua_State *L = lua_open();
	if (L) {
		// place pointer to plugin data in the L's registry -
		aPlugData->MainLuaState = L;
		lua_pushlightuserdata(L, aPlugData);
		lua_setfield(L, LUA_REGISTRYINDEX, FAR_PLUGINDATA);

		// InitLuaState(L, aPlugData, aOpenLibs);
		return 1;
	}

	return 0;
}
