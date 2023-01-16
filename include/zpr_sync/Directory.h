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
    /** \class Directory
     * @brief Represents a directory in the file system.
     *
     *@details The Directory class is used to represent a directory in the file system.
     * It contains information about the directory's path, flag, name, last modified date,
     * and the sub-directories and files within it.
     */
    class Directory
    {
    public:
        /**
        * @brief Constructor for the Directory class.
        * @param path
        * @param flag
        * @param name
        * @param last_modified The last modified date of the directory.
        * @param sub_dir A vector of sub-directories within the directory.
        * @param files A vector of files within the directory.
        */
        Directory(std::string path, std::string flag, std::string name, std::string last_modified, const std::vector<Directory> sub_dir, const std::vector<File> files);
        /**
         * @brief Adds a sub-directory to the current directory.
         * @param dir
         */
        void add_sub_dir(Directory *dir);
        /**
         * @brief Adds a file to the current directory.
         * @param file
         */
        void add_file(File *file);
        /**
         * @brief Prints the directory's information.
         */
        void print();
        /**
        * @brief Get all sub directories recursively starting from current directory
        * @return vector of all sub directories
        */
        std::vector<Directory*> get_all_sub_dir(bool root = true);
        /**
        * @brief Get all files in the current directory
        * @return map of all files in the current directory
        */
        std::map<std::string, File*> get_all_files();
        /**
        * @brief Count number of files in current directory
        * @return number of files in current directory
        */
        int count_files();
        /**
        * @brief Counts the number of subdirectories in the current directory.
        * @return The number of subdirectories in the current directory.
        */
        int count_dirs();
        int indent = 0;
        /**
         * @brief Directory path
         */
        std::string path;
        /**
         * @brief Directory flag
         */
        std::string flag;
        /**
         * @brief Directory name
         */
        std::string name;
        /**
         * @brief Directory date of the last modification
         */
        std::string last_modified;
        /**
         * @brief Sub directories
         */
        std::vector<Directory*> sub_dir;
        /**
         * @brief Files in directory
         */
        std::vector<File*> files;
        /**
         * @brief Synchronization skip
         */
        bool skip_sync = false;
        /**
         * @brief Is folder hidden
         */
        bool hidden = false;
        };
}

#endif //ZPR_SYNC_DIRECTORY_H
