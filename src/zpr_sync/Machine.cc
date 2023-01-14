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
#include <iostream>
#include <map>
#include <sstream>

namespace zpr_sync
{
    void Machine::check_working_dir()
    {
        std::string output = run_command("pwd");
        boost::trim(output);
        if (output.find("no such file or directory") != std::string::npos || output.empty())
        {
            throw std::runtime_error("Working directory  '" + this->working_dir + "' does not exist");
        }
        else
        {
            this->working_dir = output;
            Logging::info("Machine", ("Working directory: " + output));
        }
    }

    void Machine::detect_os()
    {
        std::string os = run_command("uname");
        boost::trim(os);
        if (os == "Linux")
        {
            this->os_name = RuntimeOS::Linux;
        }
        else if (os == "Darwin")
        {
            this->os_name = RuntimeOS::MacOS;
        }
        else
        {
            this->os_name = RuntimeOS::Unknown;
            throw std::runtime_error("Unsupported OS");
        }
    }

    Directory *Machine::get_current_dir()
    {
        std::string output = run_command(ls_command());
        std::istringstream input(output);
        std::string line;
        std::map<std::string, Directory *> dirs;
        if (input.good())
        {
            std::string current_path = ".";
            Directory *root_dir = new Directory(current_path, "", current_path, "", std::vector<Directory>(), std::vector<File>());
            dirs[current_path] = root_dir;
            while (getline(input, line))
            {
                std::istringstream iss(line);
                std::string token;
                std::vector<std::string> tokens = std::vector<std::string>();
                while (std::getline(iss, token, ' '))
                {
                    if (!token.empty())
                        tokens.push_back(token);
                    if (tokens.size() == 6)
                    {
                        std::getline(iss, token);
                        tokens.push_back(token);
                    }
                }
                if (line[0] == '.' && line[line.size() - 1] == ':')
                {
                    std::string new_path = line.substr(0, line.size() - 1);
                    if (new_path != current_path)
                    {
                        current_path = new_path;
                    }
                    continue;
                }
                if (tokens.size() == 7)
                {
                    if (tokens[6] == "." || tokens[6] == "..")
                    {
                        continue;
                    }
                    if (tokens[0][0] == 'd')
                    {
                        std::string sub_dir = current_path + "/" + tokens[6];
                        Directory *dir = new Directory(sub_dir, tokens[0], tokens[6], tokens[5], std::vector<Directory>(), std::vector<File>());
                        dirs[current_path]->add_sub_dir(dir);
                        dirs[sub_dir] = dir;
                    }
                    else
                    {
                        std::string file_path = current_path + "/" + tokens[6];
                        std::string ext = tokens[6].substr(tokens[6].find_last_of(".") + 1);
                        File *file = new File(file_path, get_full_path(file_path), tokens[0], tokens[6], ext, tokens[4], tokens[5], FileType::FILE);
                        file->parent_dir = dirs[current_path];
                        dirs[current_path]->add_file(file);
                    }
                }
            }
            return root_dir;
        }
        else
        {
            throw std::runtime_error("Unable to open input stream");
        }
    }

    std::string Machine::ls_command()
    {
        switch (this->os_name)
        {
        case RuntimeOS::Linux:
            return "TZ=\"UTC\" ls -la -R  --time-style=\"+%Y-%m-%dT%H:%M:%S%z\"";
        case RuntimeOS::MacOS:
            return "TZ=\"UTC\" ls -la -R  -D \"%Y-%m-%dT%H:%M:%S%z\"";
        default:
            throw std::runtime_error("Unsupported OS");
        }
    }

    std::string Machine::get_os_name()
    {
        switch (this->os_name)
        {
        case RuntimeOS::Linux:
            return "Linux";
        case RuntimeOS::MacOS:
            return "MacOS";
        default:
            throw std::runtime_error("Unsupported OS");
        }
    }

    void Machine::create_dir(std::string path)
    {
        std::string command = "mkdir -p \"" + path + "\"";
        run_command(command.c_str());
        return;
    }

    std::string Machine::get_full_path(std::string path)
    {
        std::string full_path = this->working_dir;
        if (full_path.back() != '/')
            full_path += path.substr(1);
        else
            full_path += path.substr(2);
        return full_path;
    }

    void Machine::set_modified_time(std::string path, std::string time)
    {
        std::string cmd = "TZ=\"UTC\" touch -d " + time.substr(0, time.find("+")) + " \"" + path +"\"";
        run_command(cmd.c_str());
        Logging::debug("Machine", cmd);
        return;
    }

    std::string Machine::get_file_sha(std::string path)
    {
        std::string cmd = "sha1sum \"" + path + "\"";
        std::string output = run_command(cmd.c_str());
        return output.substr(0, output.find(" "));
    }
}