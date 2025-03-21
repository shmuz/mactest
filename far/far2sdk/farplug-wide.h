#include <stdint.h>

struct PluginStartupInfo
{
	int StructSize;
	const wchar_t *ModuleName;
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

