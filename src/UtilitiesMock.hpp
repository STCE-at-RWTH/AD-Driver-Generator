#ifndef SISC_LAB_UTILITIESMOCK_HPP
#define SISC_LAB_UTILITIESMOCK_HPP

#include <gmock/gmock.h>

#include "Utilities.hpp"

class UtilitiesMock : public Utilities {
public:
    MOCK_METHOD(std::string, getAssociationByNameSignature, (), (override));
    MOCK_METHOD(std::string, createLoopSignature, (const std::string &activeVariable, int level), (override));
    MOCK_METHOD(std::string, setSeedValue, (const std::string &variable, const std::string &value_for_seeding, const std::string &loop_level), (override));
    MOCK_METHOD(std::string, initializeSeedValue, (const std::string &variable), (override));
    MOCK_METHOD(std::string, resetSeedValue, (const std::string &variable, const std::string &loop_level), (override));
    MOCK_METHOD(std::string, harvest, (const std::string &variable, const std::string &loop_level), (override));
    MOCK_METHOD(std::string, harvestVec, (const std::string &variable, const std::string &loop_level), (override));
    MOCK_METHOD(std::string, createDriverCallSignature, (), (override));
    MOCK_METHOD(std::string, createDriverCallArguments, (), (override));
    MOCK_METHOD(std::string, getModeTypeSuffix, (), (override));
};

#endif //SISC_LAB_UTILITIESMOCK_HPP