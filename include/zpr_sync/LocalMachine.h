/**
 * @file LocalMachine.h
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Local Machine class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef ZPR_SYNC_LOCALMACHINE_H
#define ZPR_SYNC_LOCALMACHINE_H

#include "zpr_sync/Machine.h"

namespace zpr_sync
{
    class LocalMachine : public Machine
    {
    public:
        LocalMachine(const char *working_dir);
        std::string run_command(const char *command);
        Directory get_current_dir();
    private:
        std::string exec(const char *cmd);
    };
}

#endif //ZPR_SYNC_LOCALMACHINE_H