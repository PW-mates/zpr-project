/**
 * @file InputArgParser.h
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains class declarations: InputArgParser - parses input arguments.
 * @version 1.0
 * @date 2022-12-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef ZPR_SYNC_INPUTARGPARSER_H
#define ZPR_SYNC_INPUTARGPARSER_H

#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>

namespace zpr_sync {
    /** \class InputArgParser
     * @brief Implements more comfortable access to program input arguments.
     *
     */
    class InputArgParser {
    public:
        /**
         * @brief Parse input arguments
         * @param argc
         * @param argv
         */
        InputArgParser(int &argc, char **argv);
        /**
         *
         * @return Hostname
         */
        std::string getHost();
        /**
         *
         * @return Username
         */
        std::string getUsername();
        /**
         *
         * @return Local path to the destination folder
         */
        std::string getPathLocal();
        /**
         *
         * @return Remote path to the destination folder (path on the server)
         */
        std::string getPathRemote();
        /**
         *
         * @return Path to the private key
         */
        std::string getKeyPath();
        /**
         *
         * @return Password
         */
        std::string getPassword();
        /**
         *
         * @return SSH Port (default 22)
         */
        int getPort();
        /**
         * @brief Print input program arguments
         */
        void showInput();
        /**
         * @brief Use verbose mode
        */
        bool isVerbose();

    private:
        /**
         * @brief Variables map
         */
        boost::program_options::variables_map vm;
    };
}

#endif //ZPR_SYNC_INPUTARGPARSER_H
