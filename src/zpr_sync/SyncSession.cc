/**
 * @file SyncSession.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the SyncSession class
 * @version 1.0
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 */

#include "zpr_sync/SyncSession.h"

namespace zpr_sync
{
    SyncSession::SyncSession(LocalMachine *local_machine, HostMachine *host_machine)
    {
        this->local_machine = local_machine;
        this->host_machine = host_machine;
    }

    void SyncSession::sync()
    {
        Logging::info("SyncSession", "Starting sync session");
        Directory *local_dir = this->local_machine->get_current_dir();
        Directory *host_dir = this->host_machine->get_current_dir();

        Logging::info("SyncSession", "Comparing local and host directories");
        Logging::info("SyncSession", "Local directory: " + std::to_string(local_dir->count_files()) + " files, " + std::to_string(local_dir->count_dirs()) + " directories");
        Logging::info("SyncSession", "Host directory: " + std::to_string(host_dir->count_files()) + " files, " + std::to_string(host_dir->count_dirs()) + " directories");
        this->sync_dirs(local_dir, host_dir);

        local_dir = this->local_machine->get_current_dir();
        host_dir = this->host_machine->get_current_dir();
        this->sync_files(local_dir, host_dir);
    }

    void SyncSession::sync_dirs(Directory *local_dir, Directory *host_dir)
    {
        std::vector<std::string> local_dirs = local_dir->get_all_sub_dir();
        std::vector<std::string> host_dirs = host_dir->get_all_sub_dir();
        for (std::string dir : local_dirs)
        {
            if (std::find(host_dirs.begin(), host_dirs.end(), dir) == host_dirs.end())
            {
                Logging::info("SyncSession", "Creating directory in Host " + dir);
                this->host_machine->create_dir(dir);
            }
        }
        for (std::string dir : host_dirs)
        {
            if (std::find(local_dirs.begin(), local_dirs.end(), dir) == local_dirs.end())
            {
                Logging::info("SyncSession", "Creating directory in Local " + dir);
                this->local_machine->create_dir(dir);
            }
        }
        Logging::info("SyncSession", "Directory structure synced");
    }

    void SyncSession::sync_files(Directory *local_dir, Directory *host_dir)
    {
        std::map<std::string, File*> local_files = local_dir->get_all_files();
        std::map<std::string, File*> host_files = host_dir->get_all_files();

        for (const auto& kv: local_files) {
            Logging::info("SyncSession", "Checking file " + kv.first);
            if (host_files.find(kv.first) == host_files.end()) {
                Logging::info("SyncSession", "File " + kv.first + " not found in Host");
                Logging::info("SyncSession", "Uploading file " + kv.first + " to Host");
                this->host_machine->upload_file(kv.second, kv.first);
            } else {
                if (kv.second->last_modified > host_files[kv.first]->last_modified) {
                    Logging::info("SyncSession", "File " + kv.first + " is newer in Local");
                    Logging::info("SyncSession", "Uploading file " + kv.first + " to Host");
                    this->host_machine->upload_file(kv.second, kv.first);
                } else if (kv.second->last_modified < host_files[kv.first]->last_modified) {
                    Logging::info("SyncSession", "File " + kv.first + " is newer in Host");
                    Logging::info("SyncSession", "Downloading file " + kv.first + " to Local");
                    this->host_machine->download_file(host_files[kv.first], local_machine->get_full_path(kv.first));
                } else {
                    Logging::debug("SyncSession", "File " + kv.first + " is up to date");
                }
            }
        }

        for (const auto& kv: host_files) {
            Logging::info("SyncSession", "Checking file " + kv.first);
            if (local_files.find(kv.first) == local_files.end()) {
                Logging::info("SyncSession", "File " + kv.first + " not found in Local");
                Logging::info("SyncSession", "Downloading file " + kv.first + " to Local");
                this->host_machine->download_file(kv.second, local_machine->get_full_path(kv.first));
            }
        }

    }
}