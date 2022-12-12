//
// Created by andrii on 10.12.22.
//

/**
 * @file Connection.cc
 * @author Andrii Demydenko
 * @brief test
 * @version 1.0
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */
# include "zpr_sync/Connection.h"
namespace zpr_sync {
    Connection::Connection(const void *user, const char *password, int port) {
        int rc;
        session = ssh_new();
        if (session == nullptr) exit(-1);
        ssh_options_set(session, SSH_OPTIONS_HOST, "localhost");
        ssh_options_set(session, SSH_OPTIONS_PORT, &port);
        ssh_options_set(session, SSH_OPTIONS_USER, user);

        printf("Connecting...\n");
        rc = ssh_connect(session);
        if (rc != SSH_OK) error();

        printf("Password Autentication...\n");
        printf("pass"); //to change
        printf("\n");
        rc = ssh_userauth_password(session, nullptr, password);
        if (rc != SSH_AUTH_SUCCESS) error();
    }

    std::string Connection::execute_command(const char *cmd) {
        unsigned int nbytes;
        std::string response;
        char buffer[1024];
        ssh_channel channel;
        int rc;

        printf("Channel...\n");
        channel = ssh_channel_new(session);
        if (channel == nullptr) exit(-1);

        printf("Opening...\n");
        rc = ssh_channel_open_session(channel);
        if (rc != SSH_OK) error();

        printf("Executing remote command...\n");
        rc = ssh_channel_request_exec(channel, cmd);
        if (rc != SSH_OK) error();

        printf("Received:\n");
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        while (nbytes > 0) {
            response += buffer;
            nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        }
        free_channel(channel);
        return response;
    }

     void Connection::free_channel(ssh_channel channel) {
        ssh_channel_send_eof(channel);
        ssh_channel_close(channel);
        ssh_channel_free(channel);
    }

    void Connection::free_session() {
        ssh_disconnect(session);
        ssh_free(session);
    }

    void Connection::error() {
        fprintf(stderr, "Error: %s\n", ssh_get_error(session));
        free_session();
        exit(-1);
    }

    Connection::~Connection() {
        printf("close connection");
        free_session();
    }
}