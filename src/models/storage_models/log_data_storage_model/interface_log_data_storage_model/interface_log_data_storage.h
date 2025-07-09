
/*
 =================================================================================================================
 Name        : interface_track_data_storage.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 11/06/2025
 Description : Interface model for storing own ship attitude data
 =================================================================================================================
*/

#pragma once
#include <vector>
#include "../../../../globals/data_types/storage_data_types/log_data_storage_data_type.h"

class InterfaceLogDataStorage
{
public:
    virtual ~InterfaceLogDataStorage() = default;

    /**
     * Interface method to get own ship attitude  data from storage
     * @return own ship attitude data as OwnShipAttitudeDataStored
     */
    virtual std::vector<LogDataStored> get_log_data
    (
        std::string_view start_time,
        std::string_view end_time
    ) = 0;
    /**
     * Interface method to update own ship attitude data in storage
     * @param own_ship_attitude_data own ship attitude as OwnShipDataStored
     */
    virtual void add_log_data_batch(std::vector<LogDataStored> &log_data) = 0;
};
