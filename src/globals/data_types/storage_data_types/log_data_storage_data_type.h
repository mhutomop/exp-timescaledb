
/*
 =================================================================================================================
 Name        : own_ship_attitude_data_storage_data_type.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 16/05/2025
 Description : Data type for Own Ship Attitude Data storage data
 =================================================================================================================
*/

#pragma once
#include <string>

#pragma pack(push, 0)
struct LogDataStored {
    std::string time = "";
    uint16_t session_id = 0;
    uint16_t simulator_id = 0;
    uint16_t object_id = 0;
    double latitude_bearing = 0.0;
    double longitude_range = 0.0;
};
#pragma pack(pop)
