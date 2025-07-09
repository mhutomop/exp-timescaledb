
/*
 =================================================================================================================
 Name        : server_util.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Utility for supporting server functions
 =================================================================================================================
*/

#include "server_util.h"
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <chrono>

std::string ServerUtil::get_iso_string(time_t seconds) {
    return boost::posix_time::to_iso_extended_string(boost::posix_time::from_time_t(seconds)) + "Z";
}

std::string ServerUtil::get_iso_string_in_ms(const int64_t &ms) {
    using namespace boost::posix_time;
    using namespace boost::gregorian;

    // Create ptime from epoch
    ptime epoch(date(1970, 1, 1));
    time_duration td = milliseconds(ms);

    // Add duration to epoch
    ptime time = epoch + td;

    auto str = boost::posix_time::to_iso_extended_string(time);
    str.replace(str.find("T"), 1, " ");

    return str;
}

int64_t ServerUtil::get_timestamp_in_ms() {
    auto current_milliseconds = 
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return current_milliseconds;
}

int64_t ServerUtil::get_timestamp_in_s() {
    auto current_seconds = 
        std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return current_seconds;
}

void ServerUtil::sleep_until
(
    struct timespec &next,
    const uint16_t &time
)
{
    // Convert time_ms into seconds and nanoseconds
    time_t add_sec = time / 1000;
    int32_t add_nsec = (time % 1000) * 1'000'000L;

    // Add to existing time
    next.tv_sec += add_sec;
    next.tv_nsec += add_nsec;

    // Normalize if nanoseconds overflow
    if (next.tv_nsec >= 1'000'000'000L) {
        next.tv_nsec -= 1'000'000'000L;
        next.tv_sec += 1;
    }

    (void) clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &next, nullptr);
}
