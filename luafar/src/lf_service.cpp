#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern "C" {
  #include <lua.h>
  #include <lauxlib.h>
  #include <lualib.h>

  #include "lf_bit64.h"
  int luaopen_utf8 (lua_State *L);
}

#include "header.hpp"
#include "farplug-wide.h"
#include "lf_luafar.h"

const char FAR_PLUGINDATA[] = "far.plugindata";

PluginStartupInfo PSInfo; // DON'T ever use fields ModuleName and ModuleNumber of PSInfo
                          // because they contain data of the 1-st loaded LuaFAR plugin.
                          // Instead, get them via GetPluginData(L).

SHAREDSYMBOL int libfunc(int arg)
{
  printf("libfunc() called\n");
  appfunc();
  return 0;
}

TPluginData* GetPluginData(lua_State* L)
{
	lua_getfield(L, LUA_REGISTRYINDEX, FAR_PLUGINDATA);
	TPluginData* pd = (TPluginData*) lua_touserdata(L, -1);
	if (pd)
		lua_pop(L, 1);
	else
		luaL_error (L, "TPluginData is not available.");
	return pd;
}

void LF_Error(lua_State *L, const char* aMsg)
{
	TPluginData *pd = GetPluginData(L);
	if (!aMsg) aMsg = "<non-string error message>";
	lua_pushstring(L, pd->ModuleName);
	lua_pushstring(L, ": ");
	luaL_gsub(L, aMsg, "\n\t", "\n   ");
	lua_concat(L, 3);
	fprintf(stderr, "%s\n", lua_tostring(L,-1));
	lua_pop(L, 1);
}

static void InitLuaState (lua_State *L, TPluginData *aPlugData, lua_CFunction aOpenLibs)
{
	int idx, pos;

	lua_CFunction func_arr[] = {
		luaopen_bit64,
		luaopen_utf8,
	};

	// open Lua libraries
	luaL_openlibs(L);

	if (aOpenLibs) {
		lua_pushcfunction(L, aOpenLibs);
		lua_call(L, 0, 0);
	}

	// open more libraries
	for (idx=0; idx < ARRAYSIZE(func_arr); idx++) {
		lua_pushcfunction(L, func_arr[idx]);
		lua_call(L, 0, 0);
	}

	lua_getglobal(L, "utf8");                   //+1
	lua_getglobal(L, "string");                 //+2
	// utf8.dump = string.dump
	lua_getfield(L, -1, "dump");                //+3
	lua_setfield(L, -3, "dump");                //+2
	// utf8.rep = string.rep
	lua_getfield(L, -1, "rep");                 //+3
	lua_setfield(L, -3, "rep");                 //+2
	// getmetatable("").__index = utf8
	lua_pushliteral(L, "");                     //+3
	lua_getmetatable(L, -1);                    //+4
	lua_pushvalue(L, -4);                       //+5
	lua_setfield(L, -2, "__index");	            //+4
	lua_pop(L, 4);                              //+0
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

		aPlugData->ShareDir = (char*) malloc(strlen(aPlugData->ModuleName) + 8);
		strcpy(aPlugData->ShareDir, aPlugData->ModuleName);
		strrchr(aPlugData->ShareDir,'/')[0] = '\0';

		InitLuaState(L, aPlugData, aOpenLibs);
		return 1;
	}

	return 0;
}
