
/*
 =================================================================================================================
 Name        : environment_variables_data_type.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Environment variables data type
 =================================================================================================================
*/

#pragma once
#include <cstdint>
#include <string>

#pragma pack(push, 0)
struct PSQLConnectionData {
    std::string host;
    uint16_t port;
    std::string database_name;
    std::string username;
    std::string password;
};
#pragma pack(pop)

#pragma pack(push, 0)
struct EnvironmentVariables {
    std::string log_level;
    PSQLConnectionData psql_connection_data;
};
#pragma pack(pop)
