//
// Created by Andrii Demydenko, Minh Nguyen on 15.01.23.
//
#include "zpr_sync/LocalMachine.h"
#include <gtest/gtest.h>

namespace zpr_sync {
    TEST(LocalMachineTest, RunCommandTest) {
        LocalMachine machine("/");

        std::string output = machine.run_command("ls");
        EXPECT_FALSE(output.empty());

        try {
            LocalMachine machine2("/non-existent-directory");
            FAIL() << "Expected std::runtime_error";
        } catch (std::runtime_error const &err) {
            EXPECT_EQ(err.what(), std::string("Working directory  '/non-existent-directory' does not exist"));
        }
    }

    TEST(LocalMachineTest, DetectOSTest) {
        LocalMachine machine("/");

#ifdef __linux__
        EXPECT_EQ(machine.get_os_name(), "Linux");
#elif __APPLE__
        EXPECT_EQ(machine.get_os_name(), "MacOS");
#endif

    }
}