#include <stdio.h>
#include <dlfcn.h>
#include "header.hpp"

typedef void (*PLUGFUNC)();

int main(int argc, const char* argv[])
{
  void *handle = dlopen("./Plugins/luafar/myplug/plug/myplug.far-plug-wide", RTLD_LAZY|RTLD_GLOBAL);
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

// SHAREDSYMBOL void appfunc()
// {
//   printf("appfunc() called\n");
// }

