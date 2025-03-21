#include <stdio.h>
#include <dlfcn.h>

#include "farplug-wide.h"
#include "header.hpp"

typedef void (*PLUGFUNC)();
typedef void (*PLUGINSETSTARTUPINFOW)(const PluginStartupInfo *Info);

#ifdef __APPLE__
  const char *Lib = "/opt/homebrew/lib/libluajit-5.1.dylib";
#else
  const char *Lib = "libluajit-5.1.so";
#endif

const char *PluginPath = "./Plugins/luafar/myplug/plug/myplug.far-plug-wide";

int main(int argc, const char* argv[])
{
  void *handle = dlopen(Lib, RTLD_LAZY|RTLD_GLOBAL);
  printf(handle ? "LuaJIT was found\n" : "LuaJIT was NOT found\n");

  void *handle2 = dlopen(PluginPath, RTLD_LAZY|RTLD_GLOBAL);
  if (handle2) {
    PLUGINSETSTARTUPINFOW plugfunc = (PLUGINSETSTARTUPINFOW) dlsym(handle2, "SetStartupInfoW");
    if (plugfunc) {
      PluginStartupInfo Info = { sizeof(PluginStartupInfo) };
      plugfunc(&Info);
    }
    else
      printf("no SetStartupInfoW found: %s\n", dlerror());
  }
  else
    printf("no handle %s\n", dlerror());

  return 0;
}
