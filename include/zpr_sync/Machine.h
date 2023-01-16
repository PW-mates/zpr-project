/**
 * @file Machine.h
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Machine class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef ZPR_SYNC_MACHINE_H
#define ZPR_SYNC_MACHINE_H

#include "zpr_sync/Directory.h"
#include <string>

namespace zpr_sync {
    enum class RuntimeOS : int {
        Linux = 0,
        MacOS = 1,
        Unknown = 2
    };
    /**
     * \class Machine
     * @brief This class is an abstract class that defines common functionality for a machine
     * that can run commands and perform file operations. It provides basic functionality such
     * as getting the current working directory, creating a directory, detecting the operating
     * system, and getting the full path of a file.
     */
    class Machine
    {
        public:
            virtual ~Machine() = default;
            /**
             * @brief Runs a command on the machine's terminal.
             * @param command
             * @return
             */
            virtual std::string run_command(std::string command) = 0;
            /**
             * @brief Returns the current working directory as a Directory object.
             * @return A pointer to the current working directory.
             */
            Directory* get_current_dir();
            /**
             * @brief Creates a new directory at the specified path.
             * @param path
             */
            void create_dir(std::string path);
            /**
             * @brief Detects the operating system of the machine.
             */
            void detect_os();
            /**
             * @brief Checks if the current working directory exists and is accessible.
             */
            void check_working_dir();
            /**
             * @brief The current working directory of the machine.
             */
            std::string working_dir;
            /**
             * @brief The operating system of the machine.
             */
            RuntimeOS os_name;
            /**
             * @brief Returns the name of the operating system as a string.
             * @return The name of the operating system.
             */
            std::string get_os_name();
            /**
             * @brief Returns the full path of a file or directory.
             * @param path
             * @return The full path of the file or directory.
             */
            std::string get_full_path(std::string path);
            /**
             * @brief Sets the modified time of a provided file path
             * @param path
             * @param time
             */
            void set_modified_time(std::string path, std::string time);
            /**
             * @brief Get the SHA1 hash of a file on the machine
             * @param path
             * @return A string containing the SHA1 hash of the file
             */
            std::string get_file_sha(std::string path);
        private:
            std::string ls_command();
    };
}

#endif //ZPR_SYNC_MACHINE_H