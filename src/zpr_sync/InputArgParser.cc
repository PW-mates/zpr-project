//
// Created by andrii on 14.12.22.
//
#include "zpr_sync/InputArgParser.h"

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
//        if (vm.count("input-data")) {
//            cout << "input data are: " << endl;
//            for(int i = 0; i < vm["input-data"].as< vector<string> >().size(); i++)
//                cout << vm["input-data"].as< vector<string> >()[i] << endl;
//        }
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
    void InputArgParser::showInput() {
        printf("username: %s\n", this->getUsername().c_str());
        printf("host: %s\n", this->getHost().c_str());
        printf("path-local: %s\n", this->getPathLocal().c_str());
        printf("path-remote: %s\n", this->getPathRemote().c_str());
        printf("key: %s\n", this->getKeyPath().c_str());
        printf("password: %s\n", this->getPassword().c_str());
        printf("port: %u\n", this->getPort());
    }
}