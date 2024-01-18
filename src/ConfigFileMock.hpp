#ifndef SISC_LAB_CONFIGFILEMOCK_HPP
#define SISC_LAB_CONFIGFILEMOCK_HPP

#include <gmock/gmock.h>
#include "ConfigFile.hpp"

class ConfigFileMock : public ConfigFile {
public:
    MOCK_METHOD(bool, validateInput, (), (override));
    MOCK_METHOD(std::string, getLanguage, (), (const, override));
    MOCK_METHOD(std::vector<CallSignature>, getFunctions, (), (const, override));
    MOCK_METHOD(void, readYamlFile, (std::string const &), (override));
    MOCK_METHOD(std::string, getActiveVariables, (), (const, override));

};

#endif //SISC_LAB_CONFIGFILEMOCK_HPP
