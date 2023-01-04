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
#include "zpr_sync/File.h"

namespace zpr_sync
{
    class HostMachine : public Machine
    {
    public:
        HostMachine(Connection *conn, std::string working_dir);
        std::string run_command(std::string command);
        std::string upload_file(File* local_path, std::string remote_path);
        std::string download_file(File* remote_path, std::string local_path);
    private:
        std::string exec(std::string cmd);
        Connection *connection;
    };
}

#endif //ZPR_SYNC_HOSTMACHINE_H