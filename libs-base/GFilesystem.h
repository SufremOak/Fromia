#ifndef GFILESYSTEM_H
#define GFILESYSTEM_H

#include "fromia.h"
#include <sys/stat.h>
#include <dirent.h>

namespace Fromia {

    // File operations
    bool fileExists(const char* path) {
        struct stat buffer;
        return (stat(path, &buffer) == 0);
    }

    bool createDirectory(const char* path) {
        if (mkdir(path, 0777) == 0) {
            log("Directory created successfully.");
            return true;
        } else {
            error("Failed to create directory.");
            return false;
        }
    }

    bool removeFile(const char* path) {
        if (remove(path) == 0) {
            log("File removed successfully.");
            return true;
        } else {
            error("Failed to remove file.");
            return false;
        }
    }

    void listDirectory(const char* path) {
        DIR* dir = opendir(path);
        if (dir == NULL) {
            error("Failed to open directory.");
            return;
        }

        struct dirent* entry;
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    }
}

#endif // GFILESYSTEM_H
