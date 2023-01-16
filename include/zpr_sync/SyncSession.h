/**
 * @file SyncSession.h
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the SyncSession class
 * @version 1.0
 * @date 2023-01-04
 * 
 * @copyright Copyright (c) 2023
*/

#ifndef ZPR_SYNC_SYNCSESSION_H
#define ZPR_SYNC_SYNCSESSION_H

#include "zpr_sync/LocalMachine.h"
#include "zpr_sync/HostMachine.h"
#include "zpr_sync/Connection.h"
#include "zpr_sync/Directory.h"
#include "zpr_sync/Logging.h"

#include <map>
#include <string>
#include <vector>
#include <algorithm>

namespace zpr_sync
{
    /**
     * \class SyncSession
     * @brief Synchronizes a local machine with a host machine by comparing the contents of their working directories.
     */
    class SyncSession
    {
    public:
        /**
         * @brief Constructs a new SyncSession with the given local and host machines.
         * @param local_machine
         * @param host_machine
         */
        SyncSession(LocalMachine *local_machine, HostMachine *host_machine);
        /**
         * @brief Synchronizes the working directories of the local and host machines.
         */
        void sync();
    private:
        /**
         * @brief A boolean value indicating whether the user chose to confirm all
         */
        bool yes_to_all = false;
        /**
         * @brief A boolean value indicating whether the user chose to decline all
         */
        bool no_to_all = false;
        /**
         * @brief Confirms whether to create the specified directory on the other machine.
         * @param dir
         * @param is_local
         * @return A boolean value indicating whether the user confirmed to create the directory on the other machine.
         */
        bool confirm_create_dir(Directory *dir, bool is_local);
        /**
         * brief Confirms whether to update the specified file on the other machine.
         * @param file1
         * @param file2
         * @param is_local
         * @return A boolean value indicating whether the user confirmed to update the file on the other machine.
         */
        bool confirm_update_file(File *file1, File *file2, bool is_local);
        /**
         * @brief Synchronizes subdirectories of the local and host directories.
         * @param local_dir
         * @param host_dir
         */
        void sync_dirs(Directory *local_dir, Directory *host_dir);
        /**
         * @brief Synchronizes files in the local and host directories.
         * @param local_dir
         * @param host_dir
         */
        void sync_files(Directory *local_dir, Directory *host_dir);
        LocalMachine *local_machine;
        HostMachine *host_machine;

    };
}

#endif
