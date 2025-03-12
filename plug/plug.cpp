#include <stdio.h>
extern "C" {

extern int libfunc(int arg);
extern void appfunc();

__attribute__ ((visibility ("default")))
void plugfunc()
{
  printf("plugfunc() called\n");
  libfunc(123);
  appfunc();
}

}
