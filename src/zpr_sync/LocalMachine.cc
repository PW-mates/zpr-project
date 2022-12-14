/**
 * @file LocalMachine.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Local Machine class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#include "zpr_sync/LocalMachine.h"
#include "zpr_sync/Logging.h"

#include <string>
#include <array>
#include <boost/algorithm/string.hpp>

namespace zpr_sync
{
    LocalMachine::LocalMachine(std::string working_dir)
    {
        this->working_dir = working_dir;
        this->check_working_dir();
        this->detect_os();
        Logging::info("Machine", ("Local machine OS: "+this->get_os_name()));
    }

    std::string LocalMachine::run_command(std::string command)
    {
        return this->exec(command);
    }

    std::string LocalMachine::exec(std::string cmd)
    {
        Logging::debug("LocalMachine", ("Executing command: "+std::string(cmd)));
        std::array<char, 128> buffer;
        std::string result;
        std::string cd_cmd = "cd " + std::string(this->working_dir) + " && ";
        std::string full_cmd = cd_cmd + std::string(cmd);
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(full_cmd.c_str(), "r"), pclose);
        if (!pipe)
        {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
        {
            result += buffer.data();
        }
        return result;
    }

}