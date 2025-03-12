#include <stdio.h>
#include <dlfcn.h>

typedef void (*PLUGFUNC)();

int main(int argc, const char* argv[])
{
  printf("main() called\n");
  auto handle = dlopen("../plug/libplug.so", RTLD_NOW|RTLD_GLOBAL);
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

extern "C"
__attribute__ ((visibility ("default")))
void appfunc()
{
  printf("appfunc() called\n");
}

