
/*
 =================================================================================================================
 Name        : psql_log_data_storage.cpp
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 11/03/2025
 Description : Model for storing SWC Gun data in PostgreSQL database
 =================================================================================================================
*/

#include "psql_log_data_storage.h"
#include <variant>
#include "../../../../utils/log_util/log_util.h"
#include "../../../../utils/server_util/server_util.h"

PSQLLogDataStorage::PSQLLogDataStorage(PSQLDatabaseAdapter* database_adapter) : database_adapter_(database_adapter)
{
    logs_mapper_ = std::make_shared<drogon::orm::Mapper<drogon_model::cms_simulator_db::Logs>>(database_adapter_->get_db_client_());
}

std::vector<LogDataStored> PSQLLogDataStorage::get_log_data
(
    std::string_view start_time,
    std::string_view end_time
)
{
    // Define time range
    auto startTime = trantor::Date::fromDbString(std::string(start_time));
    auto endTime = trantor::Date::fromDbString(std::string(end_time));

    // Build criteria
    drogon::orm::Criteria criteria = 
        drogon::orm::Criteria(drogon_model::cms_simulator_db::Logs::Cols::_time, drogon::orm::CompareOperator::GE, startTime) &&
        drogon::orm::Criteria(drogon_model::cms_simulator_db::Logs::Cols::_time, drogon::orm::CompareOperator::LE, endTime);
    
    std::vector<LogDataStored> log_stored;

    auto now = ServerUtil::get_timestamp_in_ms();

    auto results = this->logs_mapper_->findBy(criteria);

    LOG_DEBUG("Select time", std::to_string(ServerUtil::get_timestamp_in_ms() - now));

    for (const auto &log : results) {
        log_stored.emplace_back(LogDataStored{
            .time = log.getTime()->toFormattedString(false),
            .session_id = static_cast<uint16_t>(log.getValueOfSessionId()),
            .simulator_id = static_cast<uint16_t>(log.getValueOfSimulatorId()),
            .object_id = static_cast<uint16_t>(log.getValueOfObjectId()),
            .latitude_bearing = log.getValueOfLatitudeBearing(),
            .longitude_range = log.getValueOfLongitudeRange()
        });
    }

    return log_stored;
}

void PSQLLogDataStorage::add_log_data_batch(std::vector<LogDataStored> &log_data) {
    std::ostringstream sql;
        sql << "INSERT INTO " << "logs" << " (time, simulator_id, session_id, object_id, latitude_bearing, longitude_range) VALUES ";

    std::vector<std::string> placeholders;
    std::vector<std::variant<trantor::Date, int, double>> parameters;
    for (uint64_t i = 0; i < log_data.size(); ++i) {
        std::ostringstream str;
        str << "(" << "$" << i+(i*5)+1 << ", " << "$" << i+(i*5)+2 << ", " << "$" << i+(i*5)+3 << ", " << "$" << i+(i*5)+4 << ", " << "$" << i+(i*5)+5 << ", " << "$" << i+(i*5)+6 << ")";
        placeholders.push_back(str.str());

        sql << placeholders[i];
        if (i != log_data.size() - 1)
            sql << ", ";

        // Append parameters safely
        parameters.push_back(trantor::Date::fromDbStringLocal(log_data[i].time));
        parameters.push_back(log_data[i].simulator_id);
        parameters.push_back(log_data[i].session_id);
        parameters.push_back(log_data[i].object_id);
        parameters.push_back(log_data[i].latitude_bearing);
        parameters.push_back(log_data[i].longitude_range);
    }

    auto binder = (*this->database_adapter_->get_db_client_()) << sql.str();

    for (const auto &p : parameters)
    {
        std::visit([&](auto &&v) { binder << v; }, p);
    }

    binder << drogon::orm::Mode::Blocking;
    
    auto now = ServerUtil::get_timestamp_in_ms();

    binder.exec();

    LOG_DEBUG("Insert time", std::to_string(ServerUtil::get_timestamp_in_ms() - now));
}
