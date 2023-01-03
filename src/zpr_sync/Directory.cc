/**
 * @file Directory.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Directory class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#include "zpr_sync/Directory.h"

namespace zpr_sync
{
    Directory::Directory(const char *path, const char *flag, const char *name, const char *last_modified, const std::vector<Directory> sub_dir, const std::vector<File> files)
    {
        this->path = path;
        this->flag = flag;
        this->name = name;
        this->last_modified = last_modified;
    }

    void Directory::add_sub_dir(const Directory &dir)
    {
        this->sub_dir.push_back(dir);
    }

    void Directory::add_file(const File &file)
    {
        this->files.push_back(file);
    }
}