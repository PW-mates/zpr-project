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

    // zpr_sync::Connection connection(input.getUsername().c_str(),
    //                         input.getHost().c_str(),
    //                         input.getKeyPath().c_str(),
    //                         input.getPassword().c_str(),
    //                         input.getPort());
    // // const char *command = "cd ~ && ls";
    // // std::string response = connection.execute_command(command);
    // // printf("%s", response.c_str());
    // const char *local_file = "/Users/mcong/zpr-project/README2.md";
    // const char *remote_file = "/root/README.md";
    // int rc;
    // std::string response = connection.download_file(remote_file, local_file);
    // printf("%s\n", response.c_str());
    zpr_sync::LocalMachine localMachine("/Users/mcong/zpr-project");
    cout << "Hello world local!" << endl;
    cout << localMachine.run_command("ls -la") << endl;
    cout << "Done!" << endl;

    zpr_sync::Connection connection(input.getUsername().c_str(),
                            input.getHost().c_str(),
                            input.getKeyPath().c_str(),
                            input.getPassword().c_str(),
                            input.getPort());
    zpr_sync::HostMachine hostMachine(&connection, "/root/");
    cout << "Hello world remote!" << endl;
    cout << hostMachine.run_command("ls -la") << endl;
    cout << "Done!" << endl;
    return 0;
}