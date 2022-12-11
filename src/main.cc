//
// Created by andrii on 10.12.22.
//

/**
 * @file main.cc
 * @author Andrii Demydenko
 * @brief Test
 * @version 1.0
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "zpr_sync/Connection.h"

int main(int argc, char** argv) {

    zpr_sync::Connection connection(argv[1], argv[2], 22);
    const char* command = "cd ~ && ls";
    std::string response = connection.execute_command(command);
    printf("%s", response.c_str());
    return 0;
}