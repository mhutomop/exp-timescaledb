
/*
 =================================================================================================================
 Name        : config_util.cpp
 Author      : Muhammad Hutomo Padmanaba
 Version     : 0.1.0 09/06/2025
 Description : Utility for Environment Variables
 =================================================================================================================
*/

#include "config_util.h"
#include "../log_util/log_util.h"
#include "../../globals/constants.h"

void ConfigUtil::create_instance(uint8_t instance_type) {
    // Prevent race condition and make sure only one thread that access this initialization
    std::scoped_lock lock(config_util_mutex_);

    if (!config_util_instance_) {
        config_util_instance_ = std::make_shared<ConfigUtil>();

        if (instance_type == kConfigLoaderTypeGlobal)
            set_config_global();
    }
}

void ConfigUtil::set_config_global() {
    for (auto &[key, ref_value] : environment_variables_map_) {
        set_config_value(ref_value, key.data());
    }
}

void ConfigUtil::set_config_individual(const char* key, const char* value) {
    if (setenv(key, value, 1) == 0) {
        auto it = environment_variables_map_.find(key);
        if (it != environment_variables_map_.end()) {
            set_config_value(it->second, key);
        }
    } else {
        LOG_ERROR("Environment Variables Util", "Failed to set environment variable");
    }
}

void ConfigUtil::set_config_value(ValueType &ref_value, const char* key) {
    std::visit(
        [key](auto &current_ref_value) {
            using T = std::decay_t<decltype(current_ref_value.get())>;
            if constexpr (std::is_same_v<T, uint8_t>) {
                current_ref_value.get() = static_cast<uint8_t>(std::atoi(std::getenv(key)));
            } else if constexpr (std::is_same_v<T, uint16_t>) {
                current_ref_value.get() = static_cast<uint16_t>(std::atoi(std::getenv(key)));
            } else if constexpr (std::is_same_v<T, std::string>) {
                current_ref_value.get() = std::getenv(key);
            } else if constexpr (std::is_same_v<T, char>) {
                current_ref_value.get() = std::getenv(key)[0];
            } else if constexpr (std::is_same_v<T, double>) {
                current_ref_value.get() = static_cast<double>(std::stof(std::getenv(key)));
            } else if constexpr (std::is_same_v<T, int32_t>) {
                current_ref_value.get() = std::stoi(std::getenv(key));
            } else if constexpr (std::is_same_v<T, bool>) {
                std::string val = std::getenv(key);
                (void) std::transform(val.begin(), val.end(), val.begin(), ::tolower);
                current_ref_value.get() = (val == "true" || val == "1");
            } else {
                LOG_ERROR("Environment Variables Util", "Unknown type");
            }
        },
        ref_value
    );
}

EnvironmentVariables ConfigUtil::get_config(uint8_t instance_type) {
    create_instance(instance_type);
    return ConfigUtil::environment_variables_;
}
