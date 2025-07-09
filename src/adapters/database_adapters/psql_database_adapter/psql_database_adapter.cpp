
/*
 =================================================================================================================
 Name        : psql_database_adapter.cpp
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 11/03/2025
 Description : Adapter for PostgreSQL database server
 =================================================================================================================
*/

#include "psql_database_adapter.h"
#include "../../../utils/log_util/log_util.h"

PSQLDatabaseAdapter::PSQLDatabaseAdapter
(
    const char* host,
    const uint16_t &port,
    const char* database_name,
    const char* user_name,
    const char* password
)
{
    std::string url = "dbname=" + std::string(database_name) + " user=" + std::string(user_name) + 
        " password=" + std::string(password) + " host=" + std::string(host) + " port=" + std::to_string(port);
    LOG_DEBUG("DB URL", url);
	db_client_ = drogon::orm::DbClient::newPgClient(url, 10);
}

std::shared_ptr<drogon::orm::DbClient> PSQLDatabaseAdapter::get_db_client_() {
    return this->db_client_;
}
