/**
 * @file Connection.h
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains class declarations: Connection - establish connection via SSH.
 * @version 1.0
 * @date 2022-12-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ZPR_SYNC_CONNECTION_H
#define ZPR_SYNC_CONNECTION_H

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
    /** \class Connection
     * @brief Establishes a SSH connection using the private key and allows to execute commands in the server terminal.
     *
     */
    class Connection {
    public:
        /**
         * @brief Create SSH session
         * @param user
         * @param host
         * @param key_path
         * @param port
         */
        Connection(const char *user, const char *host, const char *key_path, const char *password, int port);
        /**
         * @brief Executes provided command
         * @details Open new channel; execute provided command in a remote terminal; response from
         * a server as a string; close the channel. One channel can execute only one command
         * @param command
         * @return Execution result
         */
        std::string execute_command(const char *command);
        /**
         * @brief Uploads file to the server
         * @details Open new channel; open new sftp session; open file; upload file to the server;
         * close the channel. One channel can upload only one file
         * @param local_file
         * @param remote_file
         * @return Execution result
         */
        std::string upload_file(std::string local_file, std::string remote_file);
        /**
         * @brief Downloads file from the server
         * @details Open new channel; open new sftp session; open file; download file from the server;
         * close the channel. One channel can download only one file
         * @param local_file
         * @param remote_file
         * @return Execution result
         */
        std::string download_file(std::string remote_path, std::string local_path);
        /**
         * @brief Destructor: close connection
         */
        ~Connection();

    private:
        /**
         * @brief SSH session
         */
        ssh_session session;
        /**
         * @brief Close provided channel
         * @details Send an end-of-file to the channel, close it, and free the memory that it used.
         * @param channel
         */
        static void free_channel(ssh_channel channel);
        /**
         * @brief Close SSH session
         */
        void free_session();

        /**
         * @brief Print the occurred error (should be removed)
         */
        void error();
    };
}

#endif //ZPR_SYNC_CONNECTION_H
