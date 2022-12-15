/**
 * @file main.cc
 * @author Andrii Demydenko
 * @brief Program entry point. Contains the main function, which runs subsequent program modules.
 * @version 1.0
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "zpr_sync/Connection.h"
#include "zpr_sync/InputArgParser.h"

using namespace std;

int main(int argc, char** argv) {
    zpr_sync::InputArgParser input(argc, argv);
    input.showInput();

    zpr_sync::Connection connection(input.getUsername().c_str(),
                                    input.getHost().c_str(),
                                    input.getKeyPath().c_str(),
                                    input.getPort());
    const char* command = "cd ~ && ls";
    std::string response = connection.execute_command(command);
    printf("%s", response.c_str());

    return 0;
}