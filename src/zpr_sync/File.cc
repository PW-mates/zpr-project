/**
 * @file File.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the File class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/
#include "zpr_sync/File.h"

namespace zpr_sync
{
    enum class FileType {FILE, DIRECTORY, SYMLINK, UNKNOWN};

    File::File(const char *path, const char *flag, const char *name, const char *extension, const char *size, const char *last_modified, FileType type)
    {
        this->path = path;
        this->flag = flag;
        this->name = name;
        this->extension = extension;
        this->size = size;
        this->last_modified = last_modified;
        this->type = type;
    }
}