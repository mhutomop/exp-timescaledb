
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
struct SessionDataStored {
    uint16_t id = 0;
    std::string name = "";
    std::string created_at = "";
};
#pragma pack(pop)
