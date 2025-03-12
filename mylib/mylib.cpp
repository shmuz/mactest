#include <stdio.h>
#include "header.hpp"

SHAREDSYMBOL int libfunc(int arg)
{
  printf("libfunc() called\n");
  appfunc();
  return 0;
}
