# ifdef __cplusplus
#  define SHAREDSYMBOL extern "C" __attribute__ ((visibility("default")))
# else
#  define SHAREDSYMBOL __attribute__ ((visibility("default")))
# endif

SHAREDSYMBOL void appfunc();
SHAREDSYMBOL int  libfunc(int arg);
SHAREDSYMBOL void plugfunc();

