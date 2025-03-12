#include <stdio.h>

extern "C" {

extern void appfunc();

__attribute__ ((visibility ("default")))
int libfunc(int arg)
{
  printf("appfunc() called from the library\n");
  return 0;
}

}
