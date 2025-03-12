#include <stdio.h>
#include <dlfcn.h>
#include "header.hpp"

typedef void (*PLUGFUNC)();

int main(int argc, const char* argv[])
{
  auto handle = dlopen("../plug/plug.far-plug-wide", RTLD_NOW|RTLD_GLOBAL);
  if (handle) {
    PLUGFUNC plugfunc = (PLUGFUNC) dlsym(handle, "plugfunc");
    if (plugfunc)
      plugfunc();
    else
      printf("no plugfunc: %s\n", dlerror());
  }
  else
    printf("no handle\n");
  return 0;
}

MYEXPORT void appfunc()
{
  printf("appfunc() called\n");
}

