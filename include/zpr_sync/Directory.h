/**
 * @file Directory.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Directory class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef ZPR_SYNC_DIRECTORY_H
#define ZPR_SYNC_DIRECTORY_H

#endif //ZPR_SYNC_DIRECTORY_H

#include <vector>
#include "zpr_sync/File.h"

namespace zpr_sync
{
    class Directory
    {
    public:
        Directory(const char *path, const char *flag, const char *name, const char *last_modified, const std::vector<Directory> sub_dir, const std::vector<File> files);
        void add_sub_dir(const Directory &dir);
        void add_file(const File &file);
    private:
        const char *path;
        const char *flag;
        const char *name;
        const char *last_modified;
        std::vector<Directory> sub_dir;
        std::vector<File> files;
    };
}