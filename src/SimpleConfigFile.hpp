#ifndef SIMPLECONFIGFILE_HPP
#define SIMPLECONFIGFILE_HPP

#include "ConfigFile.hpp"

class SimpleConfigFile : public ConfigFile
{
protected:
    std::string _language{};
    std::vector<CallSignature> _functions{};

public:
    SimpleConfigFile(std::string language,
                     std::string call_signature,
                     std::string active,
                     std::string mode,
                     std::string driver_type)
    {
        _language = language;
        _functions = {CallSignature(call_signature, active, mode, driver_type)};
    }

    bool validateInput() override
    {
        return absl::StrContains(_functions[0].getCallSignature(), _functions[0].getActive());
    }

    std::string getLanguage() const override { return _language; }

    std::vector<CallSignature> getFunctions() const override { return _functions; }
    CallSignature getCallSignature() const { return _functions[0]; }

    ~SimpleConfigFile() override = default;
};

#endif //SIMPLECONFIGFILE_HPP
