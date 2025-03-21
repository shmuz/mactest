#ifndef LUAFAR_H
#define LUAFAR_H

#include <farplug-wide.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <lua.h>

typedef struct
{
	const char*    ModuleName;   // copied from PluginStartupInfo
	intptr_t       ModuleNumber; // +
	uint32_t       PluginId;
	lua_State*     MainLuaState;
	uint32_t       Flags;
} TPluginData;

SHAREDSYMBOL int  LF_LuaOpen(const struct PluginStartupInfo *aInfo, TPluginData* aPlugData, lua_CFunction aOpenLibs);
// SHAREDSYMBOL int  LF_InitOtherLuaState (lua_State *L, lua_State *Lplug, lua_CFunction aOpenLibs);
// SHAREDSYMBOL void LF_LuaClose(TPluginData* aPlugData);
// SHAREDSYMBOL int  LF_Message(lua_State* L, const wchar_t* aMsg, const wchar_t* aTitle, const wchar_t* aButtons, const char* aFlags, const wchar_t* aHelpTopic, const GUID *aId);
// SHAREDSYMBOL BOOL LF_RunDefaultScript(lua_State* L);
// SHAREDSYMBOL const wchar_t *LF_Gsub (lua_State *L, const wchar_t *s, const wchar_t *p, const wchar_t *r);
// SHAREDSYMBOL LONG_PTR LF_DlgProc(lua_State *L, HANDLE hDlg, int Msg, int Param1, LONG_PTR Param2);
//
// SHAREDSYMBOL void   LF_ClosePanel (lua_State* L, HANDLE hPlugin);
// SHAREDSYMBOL int    LF_Compare (lua_State* L, HANDLE hPlugin,const struct PluginPanelItem *Item1,const struct PluginPanelItem *Item2,unsigned int Mode);
// SHAREDSYMBOL int    LF_Configure (lua_State* L, int ItemNumber);
// SHAREDSYMBOL int    LF_ConfigureV3(lua_State* L, const struct ConfigureInfo *Info);
// SHAREDSYMBOL int    LF_DeleteFiles (lua_State* L, HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber,int OpMode);
// SHAREDSYMBOL void   LF_ExitFAR (lua_State* L);
// SHAREDSYMBOL void   LF_FreeFindData (lua_State* L, HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber);
// SHAREDSYMBOL void   LF_FreeVirtualFindData (lua_State* L, HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber);
// SHAREDSYMBOL int    LF_GetFiles (lua_State* L, HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber,int Move,const wchar_t **DestPath,int OpMode);
// SHAREDSYMBOL int    LF_GetFindData (lua_State* L, HANDLE hPlugin,struct PluginPanelItem **pPanelItem,int *pItemsNumber,int OpMode);
// SHAREDSYMBOL void   LF_GetOpenPanelInfo (lua_State* L, HANDLE hPlugin,struct OpenPluginInfo *Info);
// SHAREDSYMBOL void   LF_GetPluginInfo (lua_State* L, struct PluginInfo *Info);
// SHAREDSYMBOL int    LF_GetVirtualFindData (lua_State* L, HANDLE hPlugin,struct PluginPanelItem **pPanelItem,int *pItemsNumber,const wchar_t *Path);
// SHAREDSYMBOL int    LF_MakeDirectory (lua_State* L, HANDLE hPlugin,const wchar_t **Name,int OpMode);
// SHAREDSYMBOL int    LF_MayExitFAR (lua_State* L);
// SHAREDSYMBOL HANDLE LF_OpenFilePlugin (lua_State* L, const wchar_t *Name,const unsigned char *Data,int DataSize,int OpMode);
// SHAREDSYMBOL HANDLE LF_Open (lua_State* L, int OpenFrom,INT_PTR Item);
// SHAREDSYMBOL int    LF_ProcessDialogEvent (lua_State* L, int Event,void *Param);
// SHAREDSYMBOL int    LF_ProcessEditorEvent (lua_State* L, int Event,void *Param);
// SHAREDSYMBOL int    LF_ProcessEditorInput (lua_State* L, const INPUT_RECORD *Rec);
// SHAREDSYMBOL int    LF_ProcessPanelEvent (lua_State* L, HANDLE hPlugin,int Event,void *Param);
// SHAREDSYMBOL int    LF_ProcessHostFile (lua_State* L, HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber,int OpMode);
// SHAREDSYMBOL int    LF_ProcessKey (lua_State* L, HANDLE hPlugin,int Key,unsigned int ControlState);
// SHAREDSYMBOL int    LF_ProcessSynchroEvent (lua_State* L, int Event,void *Param);
// SHAREDSYMBOL int    LF_ProcessViewerEvent (lua_State* L, int Event,void *Param);
// SHAREDSYMBOL int    LF_PutFiles (lua_State* L, HANDLE hPlugin,struct PluginPanelItem *PanelItem,int ItemsNumber,int Move,const wchar_t *SrcPath,int OpMode);
// SHAREDSYMBOL int    LF_SetDirectory (lua_State* L, HANDLE hPlugin,const wchar_t *Dir,int OpMode);
// SHAREDSYMBOL int    LF_SetFindList (lua_State* L, HANDLE hPlugin,const struct PluginPanelItem *PanelItem,int ItemsNumber);
// SHAREDSYMBOL int    LF_GetCustomData(lua_State* L, const wchar_t *FilePath, wchar_t **CustomData);
// SHAREDSYMBOL void   LF_FreeCustomData(lua_State* L, wchar_t *CustomData);
// SHAREDSYMBOL int    LF_ProcessConsoleInput(lua_State* L, INPUT_RECORD *Rec);
// SHAREDSYMBOL int    LF_GetLinkTarget(lua_State *L, HANDLE hPlugin,	struct PluginPanelItem *PanelItem, wchar_t *Target, size_t TargetSize, int OpMode);
// SHAREDSYMBOL int    LF_Analyse(lua_State *L, const struct AnalyseData *Data);

#ifdef __cplusplus
}
#endif

#endif // LUAFAR_H
