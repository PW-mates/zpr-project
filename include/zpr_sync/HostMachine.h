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
    /**
     * \class HostMachine
     * @brief Represents the remote machine that is being synced with the local machine.
     * It inherits from the Machine class and adds functionality for uploading and downloading files
     * using a provided Connection object.
     */
    class HostMachine : public Machine
    {
    public:
        /**
         * @brief Constructor for creating a new HostMachine object.
         * @param conn A pointer to a Connection object used to establish a connection to the remote machine.
         * @param working_dir
         */
        HostMachine(Connection *conn, std::string working_dir);
        /**
         * @brief Runs a command on the remote machine.
         * @param command
         * @return Response
         */
        std::string run_command(std::string command);
        /**
         * @brief Uploads a file from the local machine to the remote machine.
         * @param local_path
         * @param remote_path
         * @return Response
         */
        std::string upload_file(File* local_path, std::string remote_path);
        /**
         * @brief Downloads a file from the remote machine to the local machine.
         * @param remote_path
         * @param local_path
         * @return Response
         */
        std::string download_file(File* remote_path, std::string local_path);
    private:
        /**
         * @brief private method that runs a command on the remote machine through the provided connection
         * @param cmd
         * @return
         */
        std::string exec(std::string cmd);
        /**
         * @brief A pointer to a Connection object (private)
         */
        Connection *connection;
    };
}

#endif //ZPR_SYNC_HOSTMACHINE_H