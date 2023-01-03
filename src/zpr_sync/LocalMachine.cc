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
    LocalMachine::LocalMachine(const char *working_dir)
    {
        this->working_dir = working_dir;
        this->detect_os();
        Logging::info("Machine", ("Local machine OS: "+std::string(this->os_name)).c_str());
    }

    std::string LocalMachine::run_command(const char *command)
    {
        return this->exec(command);
    }

    Directory LocalMachine::get_current_dir()
    {
        // TODO: Implement
        return Directory("", "", "", "", std::vector<Directory>(), std::vector<File>());
    }

    std::string LocalMachine::exec(const char *cmd)
    {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
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