#include <stdio.h>
#include "header.hpp"

MYEXPORT void plugfunc()
{
  printf("plugfunc() called\n");
  libfunc(123);
}
