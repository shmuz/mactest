# ifdef __cplusplus
#  define SHAREDSYMBOL extern "C" __attribute__ ((visibility("default")))
# else
#  define SHAREDSYMBOL __attribute__ ((visibility("default")))
# endif

#ifndef ARRAYSIZE
#define ARRAYSIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#endif

SHAREDSYMBOL void appfunc();
SHAREDSYMBOL int  libfunc(int arg);
SHAREDSYMBOL void plugfunc();

