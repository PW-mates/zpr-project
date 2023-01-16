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
    /** \class File
     * @brief Represents a file on the local/remote machine.
     *
     */
    class File
    {
    public:
        /**
        * @brief Constructor for the File class.
        * @param path
        * @param full_path
        * @param flag
        * @param name
        * @param extension
        * @param size
        * @param last_modified
        * @param type
        */
        File(std::string path, std::string full_path, std::string flag, std::string name, std::string extension, std::string size, std::string last_modified, FileType type);
        /**
         * @brief File path
         */
        std::string path;
        /**
         * @brief File absolute path
         */
        std::string full_path;
        /**
         * @brief File flag
         */
        std::string flag;
        /**
         * @brief File name
         */
        std::string name;
        /**
         * @brief File extension
         */
        std::string extension;
        /**
         * @brief File size
         */
        std::string size;
        /**
         * @brief File date of the last modification
         */
        std::string last_modified;
        /**
         * @brief File type
         */
        FileType type;
        /**
         * @brief Parent directory
         */
        Directory *parent_dir;
        /**
         * @brief Is file hidden
         */
        bool hidden = false;
    };
}

#endif // ZPR_SYNC_FILE_H