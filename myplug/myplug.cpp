#include <stdio.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "header.hpp"
#include "farplug-wide.h"

SHAREDSYMBOL void SetStartupInfoW(const struct PluginStartupInfo *Info)
{
  printf("Called %s of %s\n", __FUNCTION__, Info->ModuleName);
  libfunc(123);
}
