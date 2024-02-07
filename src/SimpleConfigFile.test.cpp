#include "gtest/gtest.h"
#include "SimpleConfigFile.hpp"

TEST (SimpleConfigFile, ValidateInput_WhenActiveVariableInCallSignature_ReturnsTrue)
{
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x)",
        "x",
        "tangent",
        "something",
        "NOT_IMPORTANT");
    EXPECT_TRUE(config_file->validateInput());
}

TEST (SimpleConfigFile, ValidateInput_WhenActiveVariableNotInCallSignature_ReturnsFalse)
{
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x)",
        "active_not_in_call_signature",
        "tangent",
        "something",
        "NOT_IMPORTANT");
    EXPECT_FALSE(config_file->validateInput());
}

TEST(SimpleConfigFile, CreateSimpleConfigFile_WhenInputInConstructor_ReturnsExpectedOutput) {
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x)",
        "x",
        "tangent",
        "something",
        "NOT_IMPORTANT");
    EXPECT_EQ("cpp", config_file->getLanguage());
    std::cout << config_file->getFirstFunction().active << std::endl;
    EXPECT_EQ("x", config_file->getFirstFunction().active);
    EXPECT_EQ("something", config_file->getFirstFunction().driver_type);
    EXPECT_EQ("tangent", config_file->getFirstFunction().mode);
    EXPECT_EQ("void f(double &x)", config_file->getFirstFunction().call_signature);
}

TEST(SimpleConfigFile, Creation_of_yaml_reader){
    std::string yamlContent = R"(
    language: cpp
    functions:
      call_signature: void f(double &x)
      active_variable: x
      mode: tangent
      driver_type: something
      output: NOT_IMPORTANT
    )";

    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>();
    config_file->readYamlFile(yamlContent);

    EXPECT_EQ("cpp", config_file->getLanguage());
    EXPECT_EQ("x", config_file->getFirstFunction().active);
    EXPECT_EQ("something", config_file->getFirstFunction().driver_type);
    EXPECT_EQ("tangent", config_file->getFirstFunction().mode);
    EXPECT_EQ("void f(double &x)", config_file->getFirstFunction().call_signature);

}


TEST(SimpleConfigFile, Check_With_Multiple_Active_ones){
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void f(double &x, double &y)",
                                                          "x,y",
                                                          "tangent",
                                                          "something",
                                                          "NOT_IMPORTANT");
    EXPECT_EQ("cpp", config_file->getLanguage());
    EXPECT_EQ("x,y", config_file->getFirstFunction().active);
    EXPECT_EQ("something", config_file->getFirstFunction().driver_type);
    EXPECT_EQ("tangent", config_file->getFirstFunction().mode);
    EXPECT_EQ("void f(double &x, double &y)", config_file->getFirstFunction().call_signature);
}

