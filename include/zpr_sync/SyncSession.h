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

namespace zpr_sync
{
    class SyncSession
    {
    public:
        SyncSession(LocalMachine *local_machine, HostMachine *host_machine);
        void sync();
    private:
        void sync_dirs(Directory *local_dir, Directory *host_dir);
        void sync_files(Directory *local_dir, Directory *host_dir);
        LocalMachine *local_machine;
        HostMachine *host_machine;
    };
}

#endif
