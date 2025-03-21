#include <stdio.h>
#include <lua.h>

#include "header.hpp"
#include "farplug-wide.h"
#include "lf_luafar.h"

static lua_State* LS;
static TPluginData PluginData;
//---------------------------------------------------------------------------

SHAREDSYMBOL void SetStartupInfoW(const struct PluginStartupInfo *aInfo)
{
	PluginData.ModuleName    = aInfo->ModuleName;
	PluginData.ModuleNumber  = aInfo->ModuleNumber;

	if (!LS && LF_LuaOpen(aInfo, &PluginData, NULL)) //includes opening "far" library
		LS = PluginData.MainLuaState;

  printf("Called %s of %s\n", __FUNCTION__, aInfo->ModuleName);
  libfunc(123);

	if (LS && !LF_RunDefaultScript(LS))  {
		LF_LuaClose(&PluginData);
		LS = NULL;
	}
}
//---------------------------------------------------------------------------

SHAREDSYMBOL void ExitFARW()
{
	if (LS) {
		LF_ExitFAR(LS);
		LF_LuaClose(&PluginData);
		LS = NULL;
	}
}
//---------------------------------------------------------------------------
