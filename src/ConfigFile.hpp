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
    virtual std::string getLanguage() const { return _language; }
    virtual std::vector<CallSignature> getFunctions() const { return _functions; }
    virtual void readYamlFile(std::string const &file_path) {};
    virtual std::string getActiveVariables() const { return {}; }
    virtual std::string getOutputVariables() const { return {}; }
    virtual std::string getMode() const { return {}; }
    virtual std::string getDriverType() const { return {}; }
};

#endif //CONFIG_FILE_HPP
