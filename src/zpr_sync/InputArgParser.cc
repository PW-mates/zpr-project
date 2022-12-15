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

using namespace std;
using namespace boost::program_options;
namespace po = boost::program_options;

namespace zpr_sync {
    InputArgParser::InputArgParser(int &argc, char **argv) {
        po::options_description desc("Allowed options");
        desc.add_options()
                ("help,h", "produce help message")
                ("path_local,pl", po::value<string>(), "folder local path")
                ("name,n", po::value<string>(), "hostname (user@1.2.3.4)")
                ("path_remote,pr", po::value<string>(), "folder remote path")
                ("key,k", po::value<string>(), "private key path")
                ("port", po::value<int>()->default_value(22), "port default 22")
                ("input-data", po::value< vector<string> >(), "unspecified data")
                ;

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
        if (vm.count("name")) {
            std::vector<std::string> strs;
            boost::split(strs, vm["name"].as<string>(), boost::is_any_of("@"));
            return strs[1];
        }
       return "";
    }

    string InputArgParser::getUsername() {
        if (vm.count("name")) {
            std::vector<std::string> strs;
            boost::split(strs, vm["name"].as<string>(), boost::is_any_of("@"));
            return strs[0];
        }
        return "";
    }

    string InputArgParser::getPathLocal() {
        if (vm.count("path_local")) {
            return vm["path_local"].as<string>();
        }
        return "";
    }

    string InputArgParser::getPathRemote() {
        if (vm.count("path_remote")) {
            return vm["path_remote"].as<string>();
        }
        return "";
    }

    string InputArgParser::getKeyPath() {
        if (vm.count("key")) {
            return vm["key"].as<string>();
        }
        return "";
    }

    int InputArgParser::getPort() {
        return vm["port"].as<int>();
    }
    void InputArgParser::showInput() {
        printf("username: %s\n", this->getUsername().c_str());
        printf("host: %s\n", this->getHost().c_str());
        printf("path-local: %s\n", this->getPathLocal().c_str());
        printf("path-remote: %s\n", this->getPathRemote().c_str());
        printf("key: %s\n", this->getKeyPath().c_str());
        printf("port: %u\n", this->getPort());
    }
}