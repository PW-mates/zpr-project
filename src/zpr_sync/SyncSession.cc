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
        this->sync_files(local_dir, host_dir);
    }

    bool SyncSession::confirm_create_dir(Directory *dir, bool is_local)
    {
        if (this->yes_to_all)
            return true;
        else if (this->no_to_all)
            return false;
        std::string input;
        std::string host_name = is_local ? "local" : "host";
        Logging::warning("SyncSession", "Directory not found on " + host_name + " machine: " + dir->path);
        Logging::warning("SyncSession", "Last modified: " + dir->last_modified);
        Logging::warning("SyncSession", "Do you want to create this directory? y (yes)/Y (yes to all)/n (no)/N (no to all)");
        std::cin >> input;
        if (input == "y")
            return true;
        else if (input == "Y")
        {
            this->yes_to_all = true;
            return true;
        }
        else if (input == "n")
            return false;
        else if (input == "N")
        {
            this->no_to_all = true;
            return false;
        }
        else
        {
            Logging::info("SyncSession", "Invalid input");
            return confirm_create_dir(dir, is_local);
        }
    }

    bool SyncSession::confirm_update_file(File *file1, File *file2, bool is_downstream)
    {
        if (this->yes_to_all)
            return true;
        else if (this->no_to_all)
            return false;
        std::string input;
        std::string host_name_from = is_downstream ? "host" : "local";
        std::string host_name_to = is_downstream ? "local" : "host";
        if (file2 == nullptr)
        {
            Logging::warning("SyncSession", "File not found on " + host_name_to + " machine: " + file1->path);
            Logging::warning("SyncSession", "Last modified: " + file1->last_modified + ", size: " + file1->size + " bytes");
        }
        else
        {
            Logging::warning("SyncSession", "File " + file1->path + " is different on " + host_name_from + " and " + host_name_to + " machines");
            Logging::warning("SyncSession", "Last modified: " + host_name_from + " -> " + file1->last_modified + ", " + host_name_to + " -> " + file2->last_modified);
            Logging::warning("SyncSession", "Size: " + host_name_from + " -> " + file1->size + " bytes, " + host_name_to + " -> " + file2->size + " bytes");
        }
        std::string action = (file2 == nullptr) ? "create" : (is_downstream ? "download" : "upload");
        Logging::warning("SyncSession", "Do you want to " + action + " this file y (yes)/Y (yes to all)/n (no)/N (no to all)");
        std::cin >> input;
        if (input == "y")
            return true;
        else if (input == "Y")
        {
            this->yes_to_all = true;
            return true;
        }
        else if (input == "n")
            return false;
        else if (input == "N")
        {
            this->no_to_all = true;
            return false;
        }
        else
        {
            Logging::info("SyncSession", "Invalid input");
            return confirm_update_file(file1, file2, is_downstream);
        }
    }

    void SyncSession::sync_dirs(Directory *local_dir, Directory *host_dir)
    {
        Logging::info("SyncSession", " --- Syncing directories ---");
        bool up_to_date = true;
        std::vector<Directory *> local_dirs = local_dir->get_all_sub_dir();
        std::vector<Directory *> host_dirs = host_dir->get_all_sub_dir();
        std::vector<std::string> local_dir_names;
        std::vector<std::string> host_dir_names;
        for (Directory *dir : local_dirs)
        {
            local_dir_names.push_back(dir->name);
        }
        for (Directory *dir : host_dirs)
        {
            host_dir_names.push_back(dir->name);
        }
        for (Directory *dir : local_dirs)
        {
            if (std::find(host_dir_names.begin(), host_dir_names.end(), dir->name) == host_dir_names.end())
            {
                if (confirm_create_dir(dir, false))
                {
                    Logging::info("SyncSession", "Creating directory in Host " + dir->name);
                    this->host_machine->create_dir(dir->name);
                }
                else
                {
                    dir->skip_sync = true;
                    Logging::info("SyncSession", "Skipping directory " + dir->name);
                }
                up_to_date = false;
            }
        }
        for (Directory *dir : host_dirs)
        {
            if (std::find(local_dir_names.begin(), local_dir_names.end(), dir->name) == local_dir_names.end())
            {
                if (confirm_create_dir(dir, true))
                {
                    Logging::info("SyncSession", "Creating directory in Local " + dir->name);
                    this->local_machine->create_dir(dir->name);
                }
                else
                {
                    dir->skip_sync = true;
                    Logging::info("SyncSession", "Skipping directory " + dir->name);
                }
                up_to_date = false;
            }
        }
        if (up_to_date)
        {
            Logging::info("SyncSession", "Directory structure is up to date");
            return;
        }
        else
        {
            Logging::info("SyncSession", "Directory structure sync complete");
        }
    }

    void SyncSession::sync_files(Directory *local_dir, Directory *host_dir)
    {
        Logging::info("SyncSession", " --- Syncing files ---");
        this->yes_to_all = false;
        this->no_to_all = false;
        bool up_to_date = true;
        std::map<std::string, File *> local_files = local_dir->get_all_files();
        std::map<std::string, File *> host_files = host_dir->get_all_files();

        for (const auto &kv : local_files)
        {
            Logging::debug("SyncSession", "Checking file " + kv.first);
            if (kv.second->parent_dir->skip_sync)
            {
                Logging::info("SyncSession", "Skipping file " + kv.first);
                continue;
            }
            if (host_files.find(kv.first) == host_files.end())
            {
                if (confirm_update_file(kv.second, nullptr, false))
                {
                    Logging::info("SyncSession", "Uploading file " + kv.first + " to Host");
                    this->host_machine->upload_file(kv.second, kv.first);
                    this->host_machine->set_modified_time(host_machine->get_full_path(kv.first), kv.second->last_modified);
                }
                else
                {
                    Logging::info("SyncSession", "Skipping file " + kv.first);
                }
                up_to_date = false;
            }
            else if (kv.second->last_modified != host_files[kv.first]->last_modified)
            {
                std::string file1_sha = local_machine->get_file_sha(kv.second->full_path);
                std::string file2_sha = host_machine->get_file_sha(host_files[kv.first]->full_path);
                if (file1_sha == file2_sha) {
                    Logging::debug("SyncSession", "Same hash, difference last modification, file " + kv.first + " is up to date");
                    if (kv.second->last_modified > host_files[kv.first]->last_modified)
                    {
                        this->host_machine->set_modified_time(host_machine->get_full_path(kv.first), kv.second->last_modified);
                    }
                    else
                    {
                        this->local_machine->set_modified_time(local_machine->get_full_path(kv.first), host_files[kv.first]->last_modified);
                    }
                    continue;
                }
                if (kv.second->last_modified > host_files[kv.first]->last_modified)
                {
                    if (confirm_update_file(kv.second, host_files[kv.first], false))
                    {
                        Logging::info("SyncSession", "Uploading file " + kv.first + " to Host");
                        this->host_machine->upload_file(kv.second, kv.first);
                        this->host_machine->set_modified_time(host_machine->get_full_path(kv.first), kv.second->last_modified);
                    }
                    else
                    {
                        Logging::info("SyncSession", "Skipping file " + kv.first);
                    }
                    up_to_date = false;
                }
                else if (kv.second->last_modified < host_files[kv.first]->last_modified)
                {
                    if (confirm_update_file(host_files[kv.first], kv.second, true))
                    {
                        Logging::info("SyncSession", "Downloading file " + kv.first + " to Local");
                        this->host_machine->download_file(host_files[kv.first], local_machine->get_full_path(kv.first));
                        this->local_machine->set_modified_time(local_machine->get_full_path(kv.first), host_files[kv.first]->last_modified);
                    }
                    else
                    {
                        Logging::info("SyncSession", "Skipping file " + kv.first);
                    }
                    up_to_date = false;
                }
            }
            else
            {
                Logging::debug("SyncSession", "File " + kv.first + " is up to date");
            }
        }

        for (const auto &kv : host_files)
        {
            Logging::debug("SyncSession", "Checking file " + kv.first);
            if (kv.second->parent_dir->skip_sync)
            {
                Logging::info("SyncSession", "Skipping file " + kv.first);
                continue;
            }
            if (local_files.find(kv.first) == local_files.end())
            {
                if (confirm_update_file(kv.second, nullptr, false))
                {
                    Logging::info("SyncSession", "Downloading file " + kv.first + " to Local");
                    this->host_machine->download_file(kv.second, local_machine->get_full_path(kv.first));
                    this->local_machine->set_modified_time(local_machine->get_full_path(kv.first), kv.second->last_modified);
                }
                else
                {
                    Logging::info("SyncSession", "Skipping file " + kv.first);
                }
                up_to_date = false;
            }
        }

        if (up_to_date)
        {
            Logging::info("SyncSession", "All files are up to date");
        }
        else
        {
            Logging::info("SyncSession", "Sync complete");
        }
    }
}