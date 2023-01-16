//
// Created by Andrii Demydenko, Minh Nguyen on 15.01.23.
//

#include <gtest/gtest.h>
#include "zpr_sync/Logging.h"
#include <regex>


namespace zpr_sync
{
    class LoggingTest : public ::testing::Test {
    protected:
        std::stringstream buffer_;
        std::streambuf *sbuf_;

        LoggingTest() {
            sbuf_ = std::cout.rdbuf();
            std::cout.rdbuf(buffer_.rdbuf());
        }

        ~LoggingTest() {
            std::cout.rdbuf(sbuf_);
        }
    };

    std::string remove_color_codes(const std::string &str) {
        std::regex color_code_regex("\033\\[[0-9;]*m");
        return std::regex_replace(str, color_code_regex, "");
    }

    std::string current_time() {
        std::time_t now = std::time(0);
        std::tm *now_tm = std::gmtime(&now);
        char buf[42];
        std::strftime(buf, 42, "%Y%m%d %X", now_tm);
        return buf;
    }

    TEST_F(LoggingTest, debug) {
        Logging::set_log_level(LogLevel::DEBUG);
        Logging::debug("group", "message");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(0, 25)), "["+current_time()+"] ");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(25, 8)), "[DEBUG] ");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(33, 5)), "group");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(38, 9)), ": message");
    }

    TEST_F(LoggingTest, info) {
        Logging::set_log_level(LogLevel::DEBUG);
        Logging::info("group", "message");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(0, 25)), "["+current_time()+"] ");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(25, 7)), "[INFO] ");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(32, 5)), "group");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(37, 9)), ": message");
    }

    TEST_F(LoggingTest, warning) {
        Logging::set_log_level(LogLevel::DEBUG);
        Logging::warning("group", "message");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(0, 25)), "["+current_time()+"] ");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(25, 10)), "[WARNING] ");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(35, 5)), "group");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(40, 9)), ": message");
    }

    TEST_F(LoggingTest, error) {
        Logging::set_log_level(LogLevel::DEBUG);
        Logging::error("group", "message");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(0, 27)), "["+current_time()+"] ");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(27, 8)), "[ERROR] ");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(35, 5)), "group");
        EXPECT_EQ(remove_color_codes(buffer_.str().substr(40, 9)), ": message");
    }

}