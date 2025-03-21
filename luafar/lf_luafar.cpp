#include <stdio.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include "header.hpp"
#include "farplug-wide.h"

SHAREDSYMBOL int libfunc(int arg)
{
  printf("libfunc() called\n");
  appfunc();
  return 0;
}
