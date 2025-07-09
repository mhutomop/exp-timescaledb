
/*
 =================================================================================================================
 Name        : app.cpp
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Main file of application
 =================================================================================================================
*/

#include <cstdint>
#include "models/storage_models/log_data_storage_model/psql_log_data_storage_model/psql_log_data_storage.h"
#include "utils/config_util/config_util.h"
#include "utils/log_util/log_util.h"
#include "utils/server_util/server_util.h"

int main(int argc, char** argv) {
    try {
        // Create PostgreSQL database adapter instance
        PSQLDatabaseAdapter psql_database_adapter
        (
            ConfigUtil::get_config().psql_connection_data.host.c_str(),
            ConfigUtil::get_config().psql_connection_data.port,
            ConfigUtil::get_config().psql_connection_data.database_name.c_str(),
            ConfigUtil::get_config().psql_connection_data.username.c_str(),
            ConfigUtil::get_config().psql_connection_data.password.c_str()
        );

        PSQLLogDataStorage log_data_storage(&psql_database_adapter);

        std::vector<LogDataStored> log_data;
        for (uint16_t i = 0; i < 10000; i++) {
            log_data.emplace_back(LogDataStored{
                .time = ServerUtil::get_iso_string_in_ms(ServerUtil::get_timestamp_in_ms()),
                .session_id = 0,
                .simulator_id = 0,
                .object_id = i,
                .latitude_bearing = -6.0,
                .longitude_range = 100.0
            });
        }

        auto now = ServerUtil::get_timestamp_in_ms();

        log_data_storage.add_log_data_batch(log_data);

        LOG_DEBUG("Add time", std::to_string(ServerUtil::get_timestamp_in_ms() - now));

        now = ServerUtil::get_timestamp_in_ms();

        auto log_data_stored = log_data_storage.get_log_data(
            ServerUtil::get_iso_string_in_ms(ServerUtil::get_timestamp_in_ms() - 1000),
            ServerUtil::get_iso_string_in_ms(ServerUtil::get_timestamp_in_ms())
        );

        LOG_DEBUG("Total records", std::to_string(log_data_stored.size()));

        LOG_DEBUG("Read time", std::to_string(ServerUtil::get_timestamp_in_ms() - now));

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    catch (const std::exception &err) {
        LOG_ERROR("Main Method", err.what());
    }

    return 0;
}
