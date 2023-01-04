/**
 * @file HostMachine.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Host Machine class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#include "zpr_sync/HostMachine.h"
#include "zpr_sync/Logging.h"

namespace zpr_sync
{
    HostMachine::HostMachine(Connection *conn, std::string working_dir)
    {
        this->connection = conn;
        this->working_dir = working_dir;
        this->check_working_dir();
        this->detect_os();
        Logging::info("Machine", ("Host machine OS: "+this->get_os_name()));
    }

    std::string HostMachine::run_command(std::string command)
    {
        return this->exec(command);
    }

    std::string HostMachine::exec(std::string cmd)
    {
        std::string cd_cmd = "cd " + std::string(this->working_dir) + " && ";
        std::string full_cmd = cd_cmd + std::string(cmd);
        std::string response = this->connection->execute_command(full_cmd.c_str());
        return response;
    }

    std::string HostMachine::upload_file(File* local_file, std::string remote_path)
    {
        std::string response = this->connection->upload_file(local_file->full_path, this->get_full_path(remote_path));
        return response;
    }

    std::string HostMachine::download_file(File* remote_file, std::string local_path)
    {
        std::string response = this->connection->download_file(remote_file->full_path, local_path);
        return response;
    }
}