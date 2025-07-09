
/*
 =================================================================================================================
 Name        : server_util.cpp
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Utility for supporting server functions
 =================================================================================================================
*/

#pragma once
#include <string>

class ServerUtil
{
public:
    /**
     * Method to convert seconds from epoch time to ISO 8601 string
     * @param seconds seconds since epoch time
     */
    static std::string get_iso_string(time_t seconds);
    /**
     * Method to convert seconds from epoch time to ISO 8601 string
     * @param ms milliseconds since epoch time
     */
    static std::string get_iso_string_in_ms(const int64_t &ms);
    /**
     * Method to get timestamp of current time
     * @return epoch time in milliseconds
     */
    static int64_t get_timestamp_in_ms();
    /**
     * Method to get timestamp of current time
     * @return epoch time in seconds
     */
    static int64_t get_timestamp_in_s();
    /**
     * Method to sleep for given time in milliseconds (avoid drift caused by process time & inconsistent delay caused by thread execution)
     * @param next next time to be checked
     * @param time time in milliseconds as uint16_t
     */
    static void sleep_until
    (
        struct timespec &next,
        const uint16_t &time
    );
};
