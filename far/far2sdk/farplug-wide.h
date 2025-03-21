#ifndef __FAR2SDK_FARPLUG_WIDE_H__
#define __FAR2SDK_FARPLUG_WIDE_H__

#include <stdint.h>

struct PluginStartupInfo
{
	int StructSize;
	const char *ModuleName;
	intptr_t ModuleNumber;
};

#ifdef __cplusplus
extern "C"
{
#endif
// Exported Functions
	void SetStartupInfoW(const struct PluginStartupInfo *Info);

#ifdef __cplusplus
};
#endif

#endif //#ifndef __FAR2SDK_FARPLUG_WIDE_H__
