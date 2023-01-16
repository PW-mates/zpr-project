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
    /**
     * \class Logging
     *
     * @brief  Handles the logging functionality for the application.
     * This class provides the functionality to log messages at different log levels (debug, info, warning, error).
     */
    class Logging
    {
    public:
        /**
         * @brief allows to configure the logging level.
         * @param level
         */
        static void set_log_level(LogLevel level);
        /**
         * @brief debug method logs a debug message to the console
         * @param group
         * @param message
         */
        static void debug(std::string group, std::string message);
        /**
         * @brief info method logs a info message to the console
         * @param group
         * @param message
         */
        static void info(std::string group, std::string message);
        /**
         * @brief warning method logs a warning message to the console
         * @param group
         * @param message
         */
        static void warning(std::string group, std::string message);
        /**
         * @brief error method logs a error message to the console
         * @param group
         * @param message
         */
        static void error(std::string group, std::string message);
        template<typename ... Args>
        static std::string string_format( const std::string& format, Args ... args );
    private:
        /**
         * @brief private method that log message to the console
         * @param level
         * @param group
         * @param message
         */
        static void log(LogLevel level, std::string group, std::string message);
        static std::string now();
        static inline LogLevel log_level = LogLevel::INFO;
    };

}



#endif //ZPR_SYNC_LOGGING_H