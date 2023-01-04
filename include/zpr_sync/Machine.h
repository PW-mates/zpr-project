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

    class Machine
    {
        public:
            virtual ~Machine() = default;
            virtual std::string run_command(std::string command) = 0;
            Directory* get_current_dir();
            void detect_os();
            void check_working_dir();
            std::string working_dir;
            RuntimeOS os_name;
            std::string get_os_name();
        private:
            std::string ls_command();
    };
}

#endif //ZPR_SYNC_MACHINE_H