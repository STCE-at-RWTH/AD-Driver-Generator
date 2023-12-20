#ifndef SIMPLECONFIGFILE_HPP
#define SIMPLECONFIGFILE_HPP

#include "absl/strings/match.h"
#include "yaml-cpp/yaml.h"

#include "ConfigFile.hpp"

class SimpleConfigFile : public ConfigFile
{
    std::string _language{};
    std::vector<CallSignature> _functions{};

public:
    SimpleConfigFile() = default;

    SimpleConfigFile(std::string_view language,
                     std::string_view call_signature,
                     std::string_view active,
                     std::string_view mode,
                     std::string_view driver_type)
                     : _language(language){
        _functions = { CallSignature(call_signature, active, mode, driver_type)};
        }

    bool validateInput() override;

    std::string getLanguage() const override { return _language; }

    std::vector<CallSignature> getFunctions() const override { return _functions; }
    CallSignature getFirstFunction() const { return _functions[0]; }

    void readYamlFile(std::string const &file_path) final;

    ~SimpleConfigFile() override = default;
};


/**
 * @brief readYamlFile into members of SimpleConfigFile
 * @param file_path path to the yaml file
 */
void SimpleConfigFile::readYamlFile(const std::string &file_path) {
    YAML::Node yamlFile = YAML::Load(file_path);
    _language = yamlFile["language"].as<std::string>();
    _functions = { CallSignature(yamlFile["functions"]["call_signature"].as<std::string>(),
                                 yamlFile["functions"]["active_variable"].as<std::string>(),
                                 yamlFile["functions"]["mode"].as<std::string>(),
                                 yamlFile["functions"]["driver_type"].as<std::string>()) };
}

/**
 * @brief validateInput however only checks if active is in call signature
 * @return bool if active is in call signature
 */
bool SimpleConfigFile::validateInput() {
    // more for a show of concept this method would need to be updated with serious checks!
    return absl::StrContains(_functions[0].call_signature, _functions[0].active);
}

#endif //SIMPLECONFIGFILE_HPP
