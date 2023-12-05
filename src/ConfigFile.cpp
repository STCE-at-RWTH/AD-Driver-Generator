#include <yaml-cpp/yaml.h>

#include "ConfigFile.hpp"
#include "absl/strings/match.h"

void ConfigFile::read_yaml_file(std::string const &file_path) {
    YAML::Node config = YAML::LoadFile(file_path);
    // all public strings should be set in this function privatly

    language = config["language"].as<std::string>();
    call_signature = config["call_signature"].as<std::string>();
    active_variable = config["active_variable"].as<std::string>();
    mode = config["mode"].as<std::string>();
    driver_type = config["driver_type"].as<std::string>();

}

void ConfigFile::validate_active_variable_in_call_signature() {
    try
    {
        if (!(absl::StrContains(call_signature, active_variable)))
            throw std::invalid_argument("Variable name not found in call signature: " + active_variable);
    } catch (std::invalid_argument &exception)
    {
        throw exception;
    }
}
