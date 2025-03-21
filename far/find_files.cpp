#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <fnmatch.h>

#include "find_files.hpp"

bool find_files(const char *directory, const char *mask, FindFilesCallback callback, void *cbdata)
{
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        return false;
    }

    while ((entry = readdir(dp)) != NULL) {
        // Skip the current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // Construct the full path of the entry
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);

        // Check if the entry is a directory
        if (entry->d_type == DT_DIR) {
            // Recursively search in the subdirectory
            if (find_files(path, mask, callback, cbdata))
              return true;
        }
        else {
            // Check if the file matches the mask
            if (fnmatch(mask, entry->d_name, 0) == 0) {
                if (callback(cbdata, entry, path))
                    return true;
            }
        }
    }

    closedir(dp);
    return false;
}
