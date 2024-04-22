#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

#include <string>
#include <absl/strings/str_split.h>
#include <absl/algorithm/container.h>

#include "CallSignature.hpp"

class ConfigFile {
    std::string _language{};
    std::vector<CallSignature> _functions{};

public:
    virtual ~ConfigFile() = default;

    virtual bool validateInput() { return false; }
    [[nodiscard]] virtual std::string getLanguage() const { return _language; }
    [[nodiscard]] virtual std::vector<CallSignature> getFunctions() const { return _functions; }
    virtual void readYamlFile(std::string const &file_path) {};
    virtual std::string getActiveVariables() const { return {}; }
    virtual std::string getOutputVariables() const { return {}; }
    
    virtual std::string getActiveVariablesVector() const { return {}; }
    virtual std::string getOutputVariablesVector() const { return {}; }
    
    virtual std::string getMode() const { return {}; }
    virtual std::string getDriverType() const { return {}; }
};

#endif //CONFIG_FILE_HPP
