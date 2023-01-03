/**
 * @file InputArgParser.cc
 * @author Andrii Demydenko
 * @brief Contains the methods of the InputArgParser class
 * @version 1.0
 * @date 2022-12-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "zpr_sync/InputArgParser.h"
#include "zpr_sync/Logging.h"

using namespace std;
using namespace boost::program_options;
namespace po = boost::program_options;

namespace zpr_sync {
    InputArgParser::InputArgParser(int &argc, char **argv) {
        po::options_description desc("Allowed options");
        desc.add_options()
                ("help", "produce help message")
                ("host,h", po::value<string>(), "hostname (user@1.2.3.4)")
                ("login,u", po::value<string>(), "login")
                ("password", po::value<string>(), "password")
                ("path-local,l", po::value<string>(), "folder local path")
                ("path-remote,r", po::value<string>(), "folder remote path")
                ("identify,i", po::value<string>(), "identify file")
                ("port,p", po::value<int>()->default_value(22), "port default 22")
                ("input-data", po::value< vector<string> >(), "unspecified data")
                ("verbose,v", "verbose output");

        // Declare which options are positional
        po::positional_options_description p;
        p.add("input-data", -1);

        // parse regular options
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        // parse positional options
        po::store(po::command_line_parser(argc, argv). options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << endl;
            exit(0);
        }
    }

    string InputArgParser::getHost() {
        if (vm.count("host")) {
            std::vector<std::string> strs;
            boost::split(strs, vm["host"].as<string>(), boost::is_any_of("@"));
            if (strs.size() > 1) {
                return strs[1];
            }
            return vm["host"].as<string>();
        }
       return "";
    }

    string InputArgParser::getUsername() {
        if (vm.count("host")) {
            std::vector<std::string> strs;
            boost::split(strs, vm["host"].as<string>(), boost::is_any_of("@"));
            if (strs.size() > 1) {
                return strs[0];
            }
        }
        if (vm.count("login")) {
            return vm["login"].as<string>();
        }
        return "";
    }

    string InputArgParser::getPathLocal() {
        if (vm.count("path-local")) {
            return vm["path_local"].as<string>();
        }
        return "";
    }

    string InputArgParser::getPathRemote() {
        if (vm.count("path-remote")) {
            return vm["path_remote"].as<string>();
        }
        return "";
    }

    string InputArgParser::getKeyPath() {
        if (vm.count("identify")) {
            return vm["identify"].as<string>();
        }
        return "";
    }

    string InputArgParser::getPassword() {
        if (vm.count("password")) {
            return vm["password"].as<string>();
        }
        return "";
    }

    int InputArgParser::getPort() {
        return vm["port"].as<int>();
    }

    bool InputArgParser::isVerbose() {
        return vm.count("verbose");
    }

    void InputArgParser::showInput() {
        Logging::debug("InputArgParser::showInput", " ------------------ Input ------------------ ");
        Logging::debug("InputArgParser", ("Username: " + this->getUsername()).c_str());
        Logging::debug("InputArgParser", ("Host: " + this->getHost()).c_str());
        Logging::debug("InputArgParser", ("Path local: " + this->getPathLocal()).c_str());
        Logging::debug("InputArgParser", ("Path remote: " + this->getPathRemote()).c_str());
        Logging::debug("InputArgParser", ("Key path: " + this->getKeyPath()).c_str());
        Logging::debug("InputArgParser", ("Password: " + this->getPassword()).c_str());
        Logging::debug("InputArgParser", ("Port: " + to_string(this->getPort())).c_str());
        Logging::debug("InputArgParser", ("Verbose: " + to_string(this->isVerbose())).c_str());
        Logging::debug("InputArgParser::showInput", " ------------------ End of args ------------------ ");
    }
}