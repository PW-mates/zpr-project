/**
 * @file Machine.cc
 * @author Andrii Demydenko, Minh Nguyen
 * @brief Contains the methods of the Logging class
 * @version 1.0
 * @date 2023-01-03
 *
 * @copyright Copyright (c) 2023
 */

#include "zpr_sync/Logging.h"


namespace zpr_sync
{
    std::string Logging::now()
    {
        std::time_t now = std::time(0);
        std::tm *now_tm = std::gmtime(&now);
        char buf[42];
        std::strftime(buf, 42, "%Y%m%d %X", now_tm);
        return buf;
    }

    void Logging::log(LogLevel level, std::string group, std::string message)
    {
        if (level >= Logging::log_level)
        {
            std::string level_str;
            switch (level)
            {
            case LogLevel::DEBUG:
                level_str = "DEBUG";
                break;
            case LogLevel::INFO:
                level_str = "INFO";
                break;
            case LogLevel::WARNING:
                level_str = "WARNING";
                break;
            case LogLevel::ERROR:
                level_str = "ERROR";
                break;
            }
            std::cout << "[" << now() << "] " << "[" << level_str << "] " << group << ": " << message << std::endl;
        }
    }

    void Logging::set_log_level(LogLevel level)
    {
        Logging::log_level = level;
    }

    void Logging::debug(std::string group, std::string message)
    {
        Logging::log(LogLevel::DEBUG, group, message);
    }

    void Logging::info(std::string group, std::string message)
    {
        Logging::log(LogLevel::INFO, group, message);
    }

    void Logging::warning(std::string group, std::string message)
    {
        Logging::log(LogLevel::WARNING, group, message);
    }

    void Logging::error(std::string group, std::string message)
    {
        Logging::log(LogLevel::ERROR, group, message);
    }

    template<typename ... Args>
    std::string Logging::string_format( const std::string& format, Args ... args )
    {
        size_t size = snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
        if( size <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
        std::unique_ptr<char[]> buf( new char[ size ] ); 
        snprintf( buf.get(), size, format.c_str(), args ... );
        std::string str = std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
        return str.c_str();
    }
}