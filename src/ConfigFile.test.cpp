#include "gtest/gtest.h"

#include "ConfigFile.hpp"

TEST(ConfigFile, active_variable_in_call_signature)
{
    // SETUP
    std::string call_signature = "double x";
    std::string active_variable = "x";

    ConfigFile::validate_active_variable_in_call_signature();
}