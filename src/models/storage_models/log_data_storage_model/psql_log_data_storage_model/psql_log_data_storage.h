
/*
 =================================================================================================================
 Name        : psql_log_data_storage.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 11/03/2025
 Description : Model for storing SWC Gun data in PostgreSQL database
 =================================================================================================================
*/

#pragma once
#include "../interface_log_data_storage_model/interface_log_data_storage.h"
#include "../../../drogon_models/log_model/Logs.h"
#include "../../../../adapters/database_adapters/psql_database_adapter/psql_database_adapter.h"

class PSQLLogDataStorage : public InterfaceLogDataStorage
{
public:
    explicit PSQLLogDataStorage(PSQLDatabaseAdapter* database_adapter);

    std::vector<LogDataStored> get_log_data
    (
        std::string_view start_time,
        std::string_view end_time
    ) override;
    void add_log_data_batch(std::vector<LogDataStored> &log_data) override;
private:
    PSQLDatabaseAdapter* database_adapter_;

    std::shared_ptr<drogon::orm::Mapper<drogon_model::cms_simulator_db::Logs>> logs_mapper_;
};
