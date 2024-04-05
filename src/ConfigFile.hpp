#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

#include <string>

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
    [[nodiscard]] virtual std::string getActiveVariables() const { return {}; }
    [[nodiscard]] virtual std::string getOutputVariables() const { return {}; }
    [[nodiscard]] virtual std::string getMode() const { return {}; }
    [[nodiscard]] virtual std::string getDriverType() const { return {}; }
};

#endif //CONFIG_FILE_HPP
