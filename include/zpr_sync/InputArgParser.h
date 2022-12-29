//
// Created by andrii on 14.12.22.
//

#ifndef ZPR_SYNC_INPUTARGPARSER_H
#define ZPR_SYNC_INPUTARGPARSER_H

#endif //ZPR_SYNC_INPUTARGPARSER_H

#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

namespace zpr_sync {
    class InputArgParser {
    public:
        InputArgParser(int &argc, char **argv);
        std::string getHost();
        std::string getUsername();
        std::string getPathLocal();
        std::string getPathRemote();
        std::string getKeyPath();
        std::string getPassword();
        int getPort();
        void showInput();

    private:
        boost::program_options::variables_map vm;
    };
}