/**
 * @file Machine.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Machine class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#include "zpr_sync/Machine.h"
#include "zpr_sync/Logging.h"
#include <boost/algorithm/string.hpp>

namespace zpr_sync
{
    void Machine::check_working_dir()
    {
        std::string output = run_command("pwd");
        boost::trim(output);
        if (output.rfind("cd: no such file or directory", 0) == 0)
        {
            throw std::runtime_error("Working directory does not exist");
        } else {
            Logging::debug("Machine", ("Working directory: "+output).c_str());
        }
    }

    void Machine::detect_os()
    {
        std::string os = run_command("uname");
        boost::trim(os);
        if (os == "Linux")
        {
            this->os_name = "Linux";
        }
        else if (os == "Darwin")
        {
            this->os_name = "MacOS";
        }
        else
        {   
            throw std::runtime_error("Unsupported OS");
        }
    }
}