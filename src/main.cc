//
// Created by andrii on 10.12.22.
//

/**
 * @file main.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Program entry point. Contains the main function, which runs subsequent program modules.
 * @version 1.0
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "zpr_sync/Connection.h"
#include "zpr_sync/InputArgParser.h"
#include "zpr_sync/LocalMachine.h"
#include "zpr_sync/HostMachine.h"
#include "zpr_sync/Logging.h"

#include "zpr_sync/SyncSession.h"

using namespace std;

int main(int argc, char **argv)
{
    zpr_sync::Logging::set_log_level(zpr_sync::LogLevel::INFO);
    zpr_sync::InputArgParser input(argc, argv);
    input.showInput();

    if (input.isVerbose())
    {
        zpr_sync::Logging::set_log_level(zpr_sync::LogLevel::DEBUG);
    }
    try
    {
        zpr_sync::LocalMachine* localMachine = new zpr_sync::LocalMachine(input.getPathLocal());
        zpr_sync::Connection* connection = new zpr_sync::Connection(input.getUsername().c_str(),
                                input.getHost().c_str(),
                                input.getKeyPath().c_str(),
                                input.getPassword().c_str(),
                                input.getPort());
        zpr_sync::HostMachine* hostMachine = new zpr_sync::HostMachine(connection, input.getPathRemote());
        zpr_sync::SyncSession* syncSession = new zpr_sync::SyncSession(localMachine, hostMachine);
        syncSession->sync();
    }
    catch (const std::exception &e)
    {
        zpr_sync::Logging::error("main", e.what());
    }
    return 0;
}
