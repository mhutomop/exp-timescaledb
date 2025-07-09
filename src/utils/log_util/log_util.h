
/*
 =================================================================================================================
 Name        : log_util.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Utility for logging
 =================================================================================================================
*/

#pragma once
#include <spdlog/spdlog.h>
#include <memory>
#include <mutex>
#include <string>

/**
* Macro to call method Logger::debug to produce specific file and line when its called
* @param exp_detail exception detail as std::string
* @param log_msg log message as std::string
*/
#define LOG_DEBUG(exp_detail, log_msg) Logger::debug(exp_detail, log_msg, __FILE__, __LINE__)
/**
* Macro to call method Logger::info to produce specific file and line when its called
* @param exp_detail exception detail as std::string
* @param log_msg log message as std::string
*/
#define LOG_INFO(exp_detail, log_msg) Logger::info(exp_detail, log_msg, __FILE__, __LINE__)
/**
* Macro to call method Logger::warn to produce specific file and line when its called
* @param exp_detail exception detail as std::string
* @param log_msg log message as std::string
*/
#define LOG_WARN(exp_detail, log_msg) Logger::warn(exp_detail, log_msg, __FILE__, __LINE__)
/**
* Macro to call method Logger::error to produce specific file and line when its called
* @param exp_detail exception detail as std::string
* @param log_msg log message as std::string
*/
#define LOG_ERROR(exp_detail, log_msg) Logger::error(exp_detail, log_msg, __FILE__, __LINE__)

class Logger {
public:
    /**
     * Method to get logger instance
     * @return logger instance as std::shared_ptr<spdlog::logger>
     */
    static std::shared_ptr<spdlog::logger> &get_instance();
    /**
     * Method to run debug logger
     * @param exp_detail exception detail as std::string_view
     * @param log_msg log message as std::string_view
     * @param file file address as pointer char
     * @param line line address as int32_t
     */
    static void debug
    (
        std::string_view exp_detail,
        std::string_view log_msg,
        const char* file,
        const int32_t &line
    );
    /**
     * Method to run debug info
     * @param exp_detail exception detail as std::string_view
     * @param log_msg log message as std::string_view
     * @param file file address as pointer char
     * @param line line address as int32_t
     */
    static void info
    (
        std::string_view exp_detail, 
        std::string_view log_msg, 
        const char* file, 
        const int32_t &line
    );
    /**
     * Method to run debug warning
     * @param exp_detail exception detail as std::string_view
     * @param log_msg log message as std::string_view
     * @param file file address as pointer char
     * @param line line address as int32_t
     */
    static void warn
    (
        std::string_view exp_detail, 
        std::string_view log_msg, 
        const char* file, 
        const int32_t &line
    );
    /**
     * Method to run debug error
     * @param exp_detail exception detail as std::string_view
     * @param log_msg log message as std::string_view
     * @param file file address as pointer char
     * @param line line address as int32_t
     */
    static void error
    (
        std::string_view exp_detail, 
        std::string_view log_msg, 
        const char* file, 
        const int32_t &line
    );
private:
    static inline std::shared_ptr<spdlog::logger> logger_instance_ = nullptr;
    static inline std::mutex logger_mutex_; 

    /**
     * Method to get spdlog log level
     * @return spdlog log level as spdlog::level::level_enum
     */
    static spdlog::level::level_enum get_log_level();
    /**
     * Method to initialize logger instance
     */
    static void init();
};
