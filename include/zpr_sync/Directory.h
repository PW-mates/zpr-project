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
#include <string>
#include <map>
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
        std::vector<Directory*> get_all_sub_dir(bool root = true);
        std::map<std::string, File*> get_all_files();
        int count_files();
        int count_dirs();
        int indent = 0;
        std::string path;
        std::string flag;
        std::string name;
        std::string last_modified;
        std::vector<Directory*> sub_dir;
        std::vector<File*> files;
        bool skip_sync = false;
    };
}

#endif //ZPR_SYNC_DIRECTORY_H
