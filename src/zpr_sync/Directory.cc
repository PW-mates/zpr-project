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
#include "zpr_sync/Logging.h"
#include <iostream>
#include <string>

namespace zpr_sync
{
    Directory::Directory(std::string path, std::string flag, std::string name, std::string last_modified, const std::vector<Directory> sub_dir, const std::vector<File> files)
    {
        this->path = path;
        this->flag = flag;
        this->name = name;
        this->last_modified = last_modified;
    }

    void Directory::add_sub_dir(Directory *dir)
    {
        this->sub_dir.push_back(dir);
    }

    void Directory::add_file(File *file)
    {
        this->files.push_back(file);
    }

    void Directory::print()
    {
        std::string line = "";
        for (int i = 0; i < this->indent; i++)
        {
            line += "-";
        }
        line += this->name;
        Logging::debug("Tree", line);
        for (auto file : this->files)
        {
            std::string file_str = "";
            for (int i = 0; i < this->indent + 1; i++)
            {
                file_str += "-";
            }
            file_str += file->name;
            Logging::debug("Tree", file_str);
        }
        for (auto &dir : this->sub_dir)
        {
            dir->indent = this->indent + 1;
            dir->print();
        }
    }
}