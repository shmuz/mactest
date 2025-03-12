#include <stdio.h>
#include "header.hpp"

MYEXPORT int libfunc(int arg)
{
  printf("libfunc() called\n");
  appfunc();
  return 0;
}
