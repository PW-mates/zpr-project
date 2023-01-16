/**
 * @file LocalMachine.h
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Local Machine class
 * @version 1.0
 * @date 2023-01-03
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef ZPR_SYNC_LOCALMACHINE_H
#define ZPR_SYNC_LOCALMACHINE_H

#include "zpr_sync/Machine.h"

namespace zpr_sync
{
    /**
     * \class LocalMachine
     * @brief Represents the local machine that is being synced with the remote machine.
     * It inherits from the Machine class and implement virtual functions from it
     *
     */
    class LocalMachine : public Machine
    {
    public:
        /**
         * @brief Constructor for creating a new LocalMachine object.
         * @param working_dir
         */
        LocalMachine(std::string working_dir);
        /**
         * @brief Runs a command on the local machine.
         * @param command
         * @return Response
         */
        std::string run_command(std::string command);
    private:
        /**
         * @brief private method that runs a command on the local machine
         * @param cmd
         * @return
         */
        std::string exec(std::string cmd);
    };
}

#endif //ZPR_SYNC_LOCALMACHINE_H