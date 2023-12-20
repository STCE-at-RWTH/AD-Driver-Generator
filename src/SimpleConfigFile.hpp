#ifndef SIMPLECONFIGFILE_HPP
#define SIMPLECONFIGFILE_HPP

#include "absl/strings/match.h"

#include "ConfigFile.hpp"


class SimpleConfigFile : public ConfigFile
{
    std::string _language{};
    std::vector<CallSignature> _functions{};

public:
    SimpleConfigFile(std::string_view language,
                     std::string_view call_signature,
                     std::string_view active,
                     std::string_view mode,
                     std::string_view driver_type)
                     : _language(language){
        _functions = { CallSignature(call_signature, active, mode, driver_type)};
        }

    bool validateInput() override
    {
        return absl::StrContains(_functions[0].getCallSignature(), _functions[0].getActive());
    }

    std::string getLanguage() const override { return _language; }

    std::vector<CallSignature> getCallSignatureVector() const override { return _functions; }
    CallSignature getCallSignature() const { return _functions[0]; }

    ~SimpleConfigFile() override = default;
};

#endif //SIMPLECONFIGFILE_HPP
