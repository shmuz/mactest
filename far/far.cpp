#include <stdio.h>
#include <dlfcn.h>
#include <string>
#include <vector>

#include "farplug-wide.h"
#include "header.hpp"
#include "find_files.hpp"

typedef void (*PLUGINSETSTARTUPINFOW)(const PluginStartupInfo *Info);

#ifdef __APPLE__
  const char *Lib = "/opt/homebrew/lib/libluajit-5.1.dylib";
#else
  const char *Lib = "libluajit-5.1.so";
#endif

std::vector<std::string> PlugPaths;

static bool FindPlugCallback(void *cbdata, const dirent *entry, const char *fullpath)
{
  PlugPaths.emplace_back(fullpath);
  return false;
}

int main(int argc, const char* argv[])
{
  void *handle = dlopen(Lib, RTLD_LAZY|RTLD_GLOBAL);
  printf(handle ? "LuaJIT was found\n" : "LuaJIT was NOT found\n");

  find_files("./Plugins", "*.far-plug-wide", FindPlugCallback, nullptr);

  for (const auto& path: PlugPaths) {
    void *handle2 = dlopen(path.c_str(), RTLD_LAZY|RTLD_GLOBAL);
    if (handle2) {
      PLUGINSETSTARTUPINFOW plugfunc = (PLUGINSETSTARTUPINFOW) dlsym(handle2, "SetStartupInfoW");
      if (plugfunc) {
        PluginStartupInfo Info = { sizeof(PluginStartupInfo), path.c_str(), 0 };
        plugfunc(&Info);
      }
      else
        printf("no SetStartupInfoW found: %s\n", dlerror());
    }
    else
      printf("no handle %s\n", dlerror());
  }

  return 0;
}
