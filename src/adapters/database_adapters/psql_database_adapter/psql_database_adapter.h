
/*
 =================================================================================================================
 Name        : psql_database_adapter.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 11/03/2025
 Description : Adapter for PostgreSQL database server
 =================================================================================================================
*/

#pragma once
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Mapper.h>

class PSQLDatabaseAdapter
{
public:
    PSQLDatabaseAdapter
    (
        const char* host,
        const uint16_t &port,
        const char* database_name,
        const char* user_name,
        const char* password
    );

    /**
     * Method to get db_client_
     * @return db_client_ as drogon::orm::DbClient
     */
    std::shared_ptr<drogon::orm::DbClient> get_db_client_();
private:
    drogon::orm::DbClientPtr db_client_;
};
