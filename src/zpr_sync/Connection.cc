/**
 * @file Connection.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Connection class
 * @version 1.0
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "zpr_sync/Connection.h"
namespace zpr_sync
{
    Connection::Connection(const char *user, const char *host, const char *key_path, const char *password, int port)
    {
        int rc;
        session = ssh_new();
        if (session == nullptr)
            exit(-1);
        ssh_options_set(session, SSH_OPTIONS_HOST, host);
        ssh_options_set(session, SSH_OPTIONS_PORT, &port);

        printf("Connecting...\n");
        rc = ssh_connect(session);
        if (rc != SSH_OK)
            error();

        if ((password != NULL) && (password[0] != '\0'))
        {
            printf("Password authentication...\n");
            rc = ssh_userauth_password(session, user, password);
            if (rc != SSH_AUTH_SUCCESS)
                error();
        }
        else
        {
            printf("Private key authentication...\n");
            rc = ssh_userauth_privatekey_file(
                session,
                user,
                key_path,
                nullptr);
            if (rc != SSH_AUTH_SUCCESS)
                error();
        }
        if (rc != SSH_AUTH_SUCCESS)
            error();
    }

    std::string Connection::execute_command(const char *cmd)
    {
        unsigned int nbytes;
        std::string response;
        char buffer[1024];
        ssh_channel channel;
        int rc;

        printf("Channel...\n");
        channel = ssh_channel_new(session);
        if (channel == nullptr)
            exit(-1);

        printf("Opening...\n");
        rc = ssh_channel_open_session(channel);
        if (rc != SSH_OK)
            error();

        printf("Executing remote command...\n");
        rc = ssh_channel_request_exec(channel, cmd);
        if (rc != SSH_OK)
            error();

        printf("Received:\n");
        nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        while (nbytes > 0)
        {
            response.append(buffer, nbytes);
            nbytes = ssh_channel_read(channel, buffer, sizeof(buffer), 0);
        }
        free_channel(channel);
        return response;
    }

    std::string Connection::upload_file(const char *local_path, const char *remote_path)
    {
        ssh_scp scp;
        int rc;
        scp = ssh_scp_new(session, SSH_SCP_WRITE | SSH_SCP_RECURSIVE, remote_path);
        if (scp == NULL)
            error();
        rc = ssh_scp_init(scp);
        if (rc != SSH_OK)
            error();
        
        // get file stats
        struct stat file_stat;
        stat(local_path, &file_stat);
        char *buffer = (char *)malloc(file_stat.st_size);
        FILE *file = fopen(local_path, "r");
        fread(buffer, file_stat.st_size, 1, file);
        fclose(file);

        // send file
        rc = ssh_scp_push_file(scp, local_path, file_stat.st_size, 0644);
        if (rc != SSH_OK)
            error();
        rc = ssh_scp_write(scp, buffer, file_stat.st_size);
        if (rc != SSH_OK)
            error();
        rc = ssh_scp_close(scp);
        if (rc != SSH_OK)
            error();
        return "OK";
    }

    void Connection::free_channel(ssh_channel channel)
    {
        ssh_channel_send_eof(channel);
        ssh_channel_close(channel);
        ssh_channel_free(channel);
    }

    void Connection::free_session()
    {
        ssh_disconnect(session);
        ssh_free(session);
    }

    void Connection::error()
    {
        fprintf(stderr, "Error: %s\n", ssh_get_error(session));
        free_session();
        exit(-1);
    }

    Connection::~Connection()
    {
        printf("close connection");
        free_session();
    }
}