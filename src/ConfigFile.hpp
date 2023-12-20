#ifndef CONFIG_FILE_HPP
#define CONFIG_FILE_HPP

#include <string>

struct CallSignature{
    std::string _call_signature{};
    std::string _active{};
    std::string _mode{};
    std::string _driver_type{};

    CallSignature( std::string_view call_signature,
        std::string_view active,
        std::string_view mode,
        std::string_view driver_type)
        : _call_signature(call_signature),
          _active(active),
          _mode(mode),
          _driver_type(driver_type) {}

    std::string getCallSignature() const { return _call_signature; }
    std::string getActive() const { return _active; }
    std::string getMode() const { return _mode; }
    std::string getDriverType() const { return _driver_type; }
};

class ConfigFile {
    std::string _language{};
    std::vector<CallSignature> _functions{};

public:
    virtual ~ConfigFile() = default;

    virtual bool validateInput() { return false; }
    virtual std::string getLanguage() const { return _language; }
    virtual std::vector<CallSignature> getCallSignatureVector() const { return _functions; }
    virtual void readYamlFile(std::string const &file_path) {};
};

#endif //CONFIG_FILE_HPP
