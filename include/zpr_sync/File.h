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

#include <vector>
#include <string>

namespace zpr_sync
{
    enum class FileType
    {
        FILE,
        DIRECTORY,
        SYMLINK,
        UNKNOWN
    };

    class Directory;

    class File
    {
    public:
        File(std::string path, std::string full_path, std::string flag, std::string name, std::string extension, std::string size, std::string last_modified, FileType type);
        std::string path;
        std::string full_path;
        std::string flag;
        std::string name;
        std::string extension;
        std::string size;
        std::string last_modified;
        FileType type;
        Directory *parent_dir;
    };
}

#endif // ZPR_SYNC_FILE_H