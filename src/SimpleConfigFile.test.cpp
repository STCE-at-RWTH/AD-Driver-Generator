#include "gtest/gtest.h"
#include "SimpleConfigFile.hpp"

TEST (SimpleConfigFile, ValidateInput_active_in_call_signature)
{
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x)",
        "x",
        "tangent",
        "something");
    EXPECT_TRUE(config_file->validateInput());
}

TEST (SimpleConfigFile, ValidateInput_active_not_in_call_signature)
{
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x)",
        "active_not_in_call_signature",
        "tangent",
        "something");
    EXPECT_FALSE(config_file->validateInput());
}

TEST(SimpleConfigFile, Return_Call_Signature){
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x)",
        "x",
        "tangent",
        "something");
    EXPECT_EQ("cpp", config_file->getLanguage());
    EXPECT_EQ("x", config_file->getCallSignature().getActive());
    EXPECT_EQ("something", config_file->getCallSignature().getDriverType());
    EXPECT_EQ("tangent", config_file->getCallSignature().getMode());
    EXPECT_EQ("void f(double &x)", config_file->getCallSignature().getCallSignature());
}
