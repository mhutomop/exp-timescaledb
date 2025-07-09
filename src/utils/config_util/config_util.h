
/*
 =================================================================================================================
 Name        : config_util.h
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Utility for Environment Variables
 =================================================================================================================
*/

#pragma once
#include <memory>
#include <cstdint>
#include <mutex>
#include <unordered_map>
#include <functional>
#include <variant>
#include "../../globals/constants.h"
#include "../../globals/data_types/environment_variables_data_type.h"

class ConfigUtil {
public:
    using ValueType = std::variant<
        std::reference_wrapper<uint8_t>,
        std::reference_wrapper<uint16_t>,
        std::reference_wrapper<std::string>,
        std::reference_wrapper<char>,
        std::reference_wrapper<double>,
        std::reference_wrapper<int32_t>,
        std::reference_wrapper<bool>
    >;
    
    /**
     * Method to initialize config instance
     * @param instance_type instance type as uint8_t
     */
    static void create_instance(uint8_t instance_type = kConfigLoaderTypeGlobal);
    /**
     * Method to set environment variable individually
     * @param key key as const char*
     * @param value value as const char*
     */
    static void set_config_individual(const char* key, const char* value);
    /**
     * Method to get environment variable
     * @param instance_type instance type as uint8_t
     * @return environment variables as EnvironmentVariables
     */
    static EnvironmentVariables get_config(uint8_t instance_type = kConfigLoaderTypeGlobal);
private:
    struct TransparentHasher {
        using is_transparent = void; // Enables heterogeneous lookup
        std::size_t operator()(std::string_view key) const noexcept {
            return std::hash<std::string_view>{}(key);
        }
    };
    
    static inline std::mutex config_util_mutex_;
    static inline std::shared_ptr<ConfigUtil> config_util_instance_ = nullptr;
    static inline EnvironmentVariables environment_variables_;
    static inline std::unordered_map<std::string_view, ValueType, TransparentHasher, std::equal_to<>> environment_variables_map_ = {
        {"LOG_LEVEL", environment_variables_.log_level},
        {"PSQL_HOST", environment_variables_.psql_connection_data.host},
        {"PSQL_PORT", environment_variables_.psql_connection_data.port},
        {"PSQL_DATABASE_NAME", environment_variables_.psql_connection_data.database_name},
        {"PSQL_USERNAME", environment_variables_.psql_connection_data.username},
        {"PSQL_PASSWORD", environment_variables_.psql_connection_data.password}
    };
    
    /**
     * Method to set global environment variables
     */
    static void set_config_global();    
    /**
     * @param ref_value reference value as ValueType
     * @param key key as const char* 
     */
    static void set_config_value(ValueType &ref_value, const char* key);
};
