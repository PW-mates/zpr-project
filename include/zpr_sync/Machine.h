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
    class Machine
    {
        public:
            virtual ~Machine() = default;
            virtual std::string run_command(const char *command) = 0;
            virtual Directory get_current_dir() = 0;
            void detect_os();
            const char *working_dir;
            const char *os_name;
    };
}

#endif //ZPR_SYNC_MACHINE_H