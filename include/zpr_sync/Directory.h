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

#include <vector>
#include "zpr_sync/File.h"

namespace zpr_sync
{
    class Directory
    {
    public:
        Directory(std::string path, std::string flag, std::string name, std::string last_modified, const std::vector<Directory> sub_dir, const std::vector<File> files);
        void add_sub_dir(Directory *dir);
        void add_file(File *file);
        void print();
        int indent = 0;
        std::string path;
        std::string flag;
        std::string name;
        std::string last_modified;
        std::vector<Directory*> sub_dir;
        std::vector<File*> files;
    };
}

#endif //ZPR_SYNC_DIRECTORY_H
