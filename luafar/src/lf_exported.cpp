//---------------------------------------------------------------------------
#include <dlfcn.h> //dlclose
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include "header.hpp"
#include "lf_luafar.h"

TPluginData* GetPluginData (lua_State* L);
void LF_Error(lua_State *L, const char* aMsg);

// taken from lua.c v5.1.2
int traceback (lua_State *L) {
	lua_getfield(L, LUA_GLOBALSINDEX, "debug");
	if (!lua_istable(L, -1)) {
		lua_pop(L, 1);
		return 1;
	}
	lua_getfield(L, -1, "traceback");
	if (!lua_isfunction(L, -1)) {
		lua_pop(L, 2);
		return 1;
	}
	lua_pushvalue(L, 1);  /* pass error message */
	lua_pushinteger(L, 2);  /* skip this function and traceback */
	lua_call(L, 2, 1);  /* call debug.traceback */
	return 1;
}

// taken from lua.c v5.1.2 (modified)
int docall (lua_State *L, int narg, int nret) {
	int status;
	int base = lua_gettop(L) - narg;  /* function index */
	lua_pushcfunction(L, traceback);  /* push traceback function */
	lua_insert(L, base);  /* put it under chunk and args */
	status = lua_pcall(L, narg, nret, base);
	lua_remove(L, base);  /* remove traceback function */
	/* force a complete garbage collection in case of errors */
	if (status != 0) lua_gc(L, LUA_GCCOLLECT, 0);
	return status;
}

// if the function is successfully retrieved, it's on the stack top; 1 is returned
// else 0 returned (and the stack is unchanged)
int GetExportFunction(lua_State* L, const char* FuncName)
{
	lua_getglobal(L, "export");
	if (lua_istable(L,-1))
	{
		lua_getfield(L, -1, FuncName);
		if (lua_isfunction(L,-1))
			return lua_remove(L,-2), 1;
		lua_pop(L,1);
	}
	return lua_pop(L,1), 0;
}

int pcall_msg (lua_State* L, int narg, int nret)
{
	// int status = lua_pcall(L, narg, nret, 0);
	int status = docall (L, narg, nret);

	if (status != 0) {
		int status2 = 1;
		DWORD *Flags = &GetPluginData(L)->Flags;

		*Flags |= PDF_PROCESSINGERROR;

		if (GetExportFunction(L, "OnError")) {
			lua_insert(L,-2);
			status2 = lua_pcall(L,1,0,0);
		}

		if (status2 != 0) {
			if (lua_isstring(L, -1)) // this check prevents crashes
				LF_Error (L, lua_tostring(L, -1));
			else
				LF_Error (L, "error object is not a string");
			lua_pop (L, 1);
		}

		*Flags &= ~PDF_PROCESSINGERROR;
	}

	return status;
}

// Run default script
BOOL RunDefaultScript(lua_State* L, int ForFirstTime)
{
	int pos = lua_gettop (L);

	// Try to load the default script from a disk file
	TPluginData* pd = GetPluginData(L);
	lua_pushstring(L, pd->ShareDir);
	lua_pushstring(L, "/");
	lua_pushstring(L, strrchr(pd->ModuleName,'/')+1);
	lua_concat(L,3);

	char* defscript = (char*)lua_newuserdata (L, lua_objlen(L,-1) + 8);
	strcpy(defscript, lua_tostring(L, -2));

	FILE *fp = NULL;
	const char delims[] = ".-";
	int status = 1;
	int i;
	for (i=0; delims[i]; i++) {
		char *end = strrchr(defscript, delims[i]);
		if (end) {
			strcpy(end, ".lua");
			if ((fp = fopen(defscript, "r")) != NULL)
				break;
		}
	}
	if (fp) {
		fclose(fp);
		status = luaL_loadfile(L, defscript);
		if (status == 0) {
			lua_pushboolean(L, ForFirstTime);
			status = pcall_msg(L,1,0);
		}
		else
			LF_Error(L, lua_tostring (L, -1));
	}
	else
		LF_Error(L, "Default script not found");

	lua_settop (L, pos);
	return (status == 0);
}

BOOL LF_RunDefaultScript(lua_State* L)
{
	return RunDefaultScript(L, 1);
}

// return FALSE only if error occurred
BOOL CheckReloadDefaultScript (lua_State *L)
{
	// reload default script?
	int reload = 0;
	lua_getglobal(L, "far");
	if (lua_istable(L, -1))
	{
		lua_getfield(L, -1, "ReloadDefaultScript");
		reload = lua_toboolean(L, -1);
		lua_pop(L, 1);
	}
	lua_pop(L, 1);
	return !reload || RunDefaultScript(L, 0);
}

void LF_LuaClose(TPluginData* aPlugData)
{
	lua_close(aPlugData->MainLuaState);
	free(aPlugData->ShareDir);
}

void LF_ExitFAR(lua_State* L)
{
	if (GetExportFunction(L, "ExitFAR"))   //+1: Func
		pcall_msg(L, 0, 0);                  //+0
}

int LF_MayExitFAR(lua_State* L)
{
	int ret = 1;
	if (GetExportFunction(L, "MayExitFAR"))  { //+1: Func
		if (!pcall_msg(L, 0, 1)) {               //+1
			ret = lua_toboolean(L,-1);
			lua_pop(L,1);                          //+0
		}
	}
	return ret;
}
