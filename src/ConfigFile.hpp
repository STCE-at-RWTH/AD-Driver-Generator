#include <string>

#include "absl/strings/match.h"

#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

struct CallSignature {
protected:
    std::string _call_signature{};
    std::string _active{};
    std::string _mode{};
    std::string _driver_type{};

public:
    CallSignature(
        std::string& call_signature,
        std::string& active,
        std::string& mode,
        std::string& driver_type)
    {
        _call_signature = call_signature;
        _active = active;
        _mode = mode;
        _driver_type = driver_type;
    }

    std::string getCallSignature() const { return _call_signature; }
    std::string getActive() const { return _active; }
    std::string getMode() const { return _mode; }
    std::string getDriverType() const { return _driver_type; }
};

class ConfigFile {
protected:
    std::string _language{};
    std::vector<CallSignature> _functions{};

public:
    virtual ~ConfigFile() = default;

    virtual bool validateInput() { return false; }
    virtual std::string getLanguage() const { return _language; }
    virtual std::vector<CallSignature> getFunctions() const { return _functions; }
};

#endif //CONFIG_FILE_HPP
