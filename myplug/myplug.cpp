#include <stdio.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "header.hpp"

SHAREDSYMBOL void SetStartupInfoW(const struct PluginStartupInfo *Info)
{
  printf("%s called\n", __FUNCTION__);
  libfunc(123);
}
