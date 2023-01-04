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
#include <algorithm>

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

    int Directory::count_files()
    {
        int count = 0;
        for (auto &dir : this->sub_dir)
        {
            count += dir->count_files();
        }
        count += this->files.size();
        return count;
    }

    int Directory::count_dirs()
    {
        int count = 0;
        for (auto &dir : this->sub_dir)
        {
            count += dir->count_dirs();
        }
        count += this->sub_dir.size();
        return count;
    }

    std::vector<std::string> Directory::get_all_sub_dir()
    {
        std::vector<std::string> sub_dirs;
        sub_dirs.push_back(this->path);
        for (auto &dir : this->sub_dir)
        {
            sub_dirs.push_back(dir->path);
            std::vector<std::string> sub_sub_dirs = dir->get_all_sub_dir();
            sub_dirs.insert(sub_dirs.end(), sub_sub_dirs.begin(), sub_sub_dirs.end());
        }
        std::sort(sub_dirs.begin(), sub_dirs.end(), [](const std::string &a, const std::string &b) {
            return a.size() < b.size();
        });
        return sub_dirs;
    }

    std::map<std::string, File *> Directory::get_all_files()
    {
        std::map<std::string, File *> all_files;
        for (auto &file : this->files)
        {
            all_files[file->path] = file;
        }
        for (auto &dir : this->sub_dir)
        {
            std::map<std::string, File *> sub_files = dir->get_all_files();
            all_files.insert(sub_files.begin(), sub_files.end());
        }
        return all_files;
    }
}