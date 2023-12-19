#include "gtest/gtest.h"
#include "SimpleConfigFile.hpp"

TEST (SimpleConfigFile, ValidateInput_active_in_call_signature)
{
    //SimpleConfigFile config_file;
    auto config_file = new SimpleConfigFile("cpp",
        "void f(double &x)",
        "x",
        "tangent",
        "something");
    EXPECT_TRUE(config_file->validateInput());
}

TEST (SimpleConfigFile, ValidateInput_active_not_in_call_signature)
{
    //SimpleConfigFile config_file;
    auto config_file = new SimpleConfigFile("cpp",
        "void f(double &x)",
        "abc",
        "tangent",
        "something");
    EXPECT_TRUE(config_file->validateInput());
}
