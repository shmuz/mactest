#ifndef FIND_FILES_HPP

#include <dirent.h>

typedef bool (*FindFilesCallback)(void *cbdata, const dirent *entry, const char *fullpath);

bool find_files(const char *directory, const char *mask, FindFilesCallback callback, void *cbdata);

#endif //#ifndef FIND_FILES_HPP
