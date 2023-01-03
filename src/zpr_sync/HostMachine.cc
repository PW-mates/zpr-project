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
    HostMachine::HostMachine(Connection *conn, const char *working_dir)
    {
        this->connection = conn;
        this->working_dir = working_dir;
        this->detect_os();
        Logging::info("Machine", ("Host machine OS: "+std::string(this->os_name)).c_str());
    }

    std::string HostMachine::run_command(const char *command)
    {
        return this->exec(command);
    }

    Directory HostMachine::get_current_dir()
    {
        // TODO: Implement
        return Directory("", "", "", "", std::vector<Directory>(), std::vector<File>());
    }

    std::string HostMachine::exec(const char *cmd)
    {
        std::string response = this->connection->execute_command(cmd);
        return response;
    }
}