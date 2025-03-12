#define MYEXPORT extern "C" __attribute__ ((visibility ("default")))

MYEXPORT void appfunc();
MYEXPORT int  libfunc(int arg);
MYEXPORT void plugfunc();

