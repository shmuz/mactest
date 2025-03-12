#include <stdio.h>
#include "header.hpp"

SHAREDSYMBOL void plugfunc()
{
  printf("plugfunc() called\n");
  libfunc(123);
}
