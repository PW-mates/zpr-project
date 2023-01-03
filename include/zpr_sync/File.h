/**
 * @file File.h
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the File class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef ZPR_SYNC_FILE_H
#define ZPR_SYNC_FILE_H

#endif //ZPR_SYNC_FILE_H

#include <vector>

namespace zpr_sync
{
    enum class FileType;

    class File
    {
    public:
        File(const char *path, const char *flag, const char *name, const char *extension, const char *size, const char *last_modified, FileType type);
    private:
        const char *path;
        const char *flag;
        const char *name;
        const char *extension;
        const char *size;
        const char *last_modified;
        FileType type;
    };
}