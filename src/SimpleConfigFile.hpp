#ifndef SIMPLECONFIGFILE_HPP
#define SIMPLECONFIGFILE_HPP

#include <absl/strings/match.h>
#include <yaml-cpp/yaml.h>

#include "ConfigFile.hpp"
#include "CallSignature.hpp"

class SimpleConfigFile : public ConfigFile
{

    std::string _language{};
    std::vector<CallSignature> _functions{};

public:
    SimpleConfigFile() = default;

    SimpleConfigFile(std::string_view language,
                     std::string_view call_signature,
                     std::string_view active,
                     std::string_view output,
                     std::string_view mode,
                     std::string_view driver_type)
                     : _language(language){
        _functions = { CallSignature(call_signature, active, output, mode, driver_type)};
        }

    bool validateInput() override;

    [[nodiscard]] CallSignature getFirstFunction() const { return _functions[0]; }
    [[nodiscard]] std::vector<CallSignature> getFunctions() const override { return _functions; }

    [[nodiscard]] std::string getLanguage() const override { return _language; }
    [[nodiscard]] std::string getActiveVariables() const override;
    [[nodiscard]] std::string getOutputVariables() const override;
    [[nodiscard]] std::string getMode() const override;
    [[nodiscard]] std::string getDriverType() const override { return _functions[0].driver_type; }
    void readYamlFile(std::string const &file_path) final;

    ~SimpleConfigFile() override = default;
};


/**
 * @brief readYamlFile into members of SimpleConfigFile
 * @param file_path path to the yaml file
 */
void SimpleConfigFile::readYamlFile(const std::string &file_path) {
    YAML::Node yamlFile = YAML::LoadFile(file_path);
    _language = yamlFile["language"].as<std::string>();
    _functions = { CallSignature(yamlFile["functions"]["call_signature"].as<std::string>(),
                                 yamlFile["functions"]["active_variable"].as<std::string>(),
                                 yamlFile["functions"]["output"].as<std::string>(),
                                 yamlFile["functions"]["mode"].as<std::string>(),
                                 yamlFile["functions"]["driver_type"].as<std::string>())};
}

/**
 * @brief validateInput however only checks if active is in call signature
 * @return bool if active is in call signature
 */
bool SimpleConfigFile::validateInput() {
    // Separate the arguments name from the call signature
    std::vector<std::string> callSignatureArguments = absl::StrSplit(_functions[0].call_signature, absl::ByAnyChar("("),  absl::SkipEmpty());
    callSignatureArguments.erase(callSignatureArguments.begin());
    // Check if active and output are in call signature
    bool isActiveInCallSignature = absl::StrContains(callSignatureArguments[0], _functions[0].active);
    bool isOutputInCallSignature = absl::StrContains(callSignatureArguments[0], _functions[0].output);
    //Check if mode and driver type are valid
    bool isModeValid = absl::StrContains(_functions[0].mode, "tangent") ||
                       absl::StrContains(_functions[0].mode, "Tangent") ||
                       absl::StrContains(_functions[0].mode, "Adjoint") ||
                       absl::StrContains(_functions[0].mode, "adjoint");
    bool isDriverTypeValid = absl::StrContains(_functions[0].driver_type, "Gradient") ||
                             absl::StrContains(_functions[0].driver_type, "gradient") ||
                             absl::StrContains(_functions[0].driver_type, "Jacobian") ||
                             absl::StrContains(_functions[0].driver_type, "jacobian") ||
                             absl::StrContains(_functions[0].driver_type, "Hessian") ||
                             absl::StrContains(_functions[0].driver_type, "hessian");
    bool validInput = isActiveInCallSignature && isOutputInCallSignature && isModeValid && isDriverTypeValid;
    return validInput;
}

std::string SimpleConfigFile::getActiveVariables() const {
    return { _functions[0].active };
}

std::string SimpleConfigFile::getOutputVariables() const {
    return { _functions[0].output };
}

std::string SimpleConfigFile::getMode() const {
    return { _functions[0].mode };
}

#endif //SIMPLECONFIGFILE_HPP