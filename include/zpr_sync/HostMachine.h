/**
 * @file HostMachine.h
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Host Machine class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef ZPR_SYNC_HOSTMACHINE_H
#define ZPR_SYNC_HOSTMACHINE_H

#include "zpr_sync/Machine.h"
#include "zpr_sync/Connection.h"

namespace zpr_sync
{
    class HostMachine : public Machine
    {
    public:
        HostMachine(Connection *conn, const char *working_dir);
        std::string run_command(const char *command);
        Directory get_current_dir();
    private:
        std::string exec(const char *cmd);
        Connection *connection;
    };
}

#endif //ZPR_SYNC_HOSTMACHINE_H