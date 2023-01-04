/**
 * @file Logging.h
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Logging class
 * @version 1.0
 * @date 2022-01-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ZPR_SYNC_LOGGING_H
#define ZPR_SYNC_LOGGING_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <memory>


namespace zpr_sync
{
    enum class LogLevel: int
    {
        DEBUG = 0,
        INFO = 1,
        WARNING = 2,
        ERROR = 3
    };

    class Logging
    {
    public:
        static void set_log_level(LogLevel level);
        static void debug(std::string group, std::string message);
        static void info(std::string group, std::string message);
        static void warning(std::string group, std::string message);
        static void error(std::string group, std::string message);
        template<typename ... Args>
        static std::string string_format( const std::string& format, Args ... args );
    private:
        static void log(LogLevel level, std::string group, std::string message);
        static std::string now();
        static inline LogLevel log_level = LogLevel::INFO;
    };

}



#endif //ZPR_SYNC_LOGGING_H