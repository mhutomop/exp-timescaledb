
/*
 =================================================================================================================
 Name        : log_util.cpp
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Utility for logging
 =================================================================================================================
*/

#include "log_util.h"
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "../../globals/constants.h"
#include "../../utils/config_util/config_util.h"

std::shared_ptr<spdlog::logger> &Logger::get_instance() {
    if (!logger_instance_)
        init();
    
    return logger_instance_;
}

void Logger::debug
(
    std::string_view exp_detail, 
    std::string_view log_msg, 
    const char* file,
    const int32_t &line
)
{
    get_instance()->log(spdlog::source_loc{file, line, SPDLOG_FUNCTION},
        spdlog::level::debug, std::string(exp_detail) + " - " + std::string(log_msg));
}

void Logger::info
(
    std::string_view exp_detail, 
    std::string_view log_msg, 
    const char* file,
    const int32_t &line
)
{
    get_instance()->log(spdlog::source_loc{file, line, SPDLOG_FUNCTION},
        spdlog::level::info, std::string(exp_detail) + " - " + std::string(log_msg));
}

void Logger::warn
(
    std::string_view exp_detail, 
    std::string_view log_msg, 
    const char* file, 
    const int32_t &line
)
{
    get_instance()->log(spdlog::source_loc{file, line, SPDLOG_FUNCTION},
        spdlog::level::warn, std::string(exp_detail) + " - " + std::string(log_msg));
}

void Logger::error
(
    std::string_view exp_detail, 
    std::string_view log_msg, 
    const char* file, 
    const int32_t &line
)
{
    get_instance()->log(spdlog::source_loc{file, line, SPDLOG_FUNCTION},
    spdlog::level::err, std::string(exp_detail) + " - " + std::string(log_msg));
}

void Logger::init() {
    // Prevent race condition and make sure only one thread that access this initialization
    std::scoped_lock lock(logger_mutex_);
    if (!logger_instance_) {
        try {
            std::string pattern = "%H:%M:%S.%e [thread %t] %^%-7l%$ %g:%# %v";

            auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            console_sink->set_pattern(pattern);

            std::string base_filename = std::string(kServiceName) + "_";

            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::tm tm;
            const auto* tm_now = localtime_r(&now, &tm);
            std::stringstream ss;
            ss << std::put_time(tm_now, "%Y-%m-%d");

            std::string filename_pattern = "logs/" + base_filename + ss.str() + ".log";

            auto file_sink = std::make_shared<spdlog::sinks::daily_file_format_sink_mt>(filename_pattern, 0, 0);
            file_sink->set_pattern(pattern);

            std::vector<spdlog::sink_ptr> sinks{ console_sink, file_sink };
            logger_instance_ = std::make_shared<spdlog::logger>("log", sinks.begin(), sinks.end());
            logger_instance_->set_level(get_log_level());
            logger_instance_->flush_on(get_log_level());
            spdlog::register_logger(logger_instance_);
        } catch (const spdlog::spdlog_ex &ex) {
            std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        }
    }
}

spdlog::level::level_enum Logger::get_log_level() {
    std::string log_level = ConfigUtil::get_config().log_level;
    if (log_level == "debug") return spdlog::level::debug;
    else if (log_level == "info") return spdlog::level::info;
    else return spdlog::level::info;
}
