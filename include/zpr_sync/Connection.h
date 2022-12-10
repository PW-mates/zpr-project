//
// Created by andrii on 10.12.22.
//

#ifndef ZPR_SYNC_CONNECTION_H
#define ZPR_SYNC_CONNECTION_H

#endif //ZPR_SYNC_CONNECTION_H

#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cstring>

namespace zpr_sync {
    class Connection {
    public:
        Connection(const void *user, const char *password, int port);

        std::string execute_command(const char *command);

        static void free_channel(ssh_channel channel);

        void free_session();

        void error();

        ~Connection();

    private:
        ssh_session session;

        int rc;

    };
}