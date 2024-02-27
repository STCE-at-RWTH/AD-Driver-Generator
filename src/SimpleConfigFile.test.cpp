#include <gtest/gtest.h>

#include "SimpleConfigFile.hpp"

TEST(SimpleConfigFile, ValidateInput_WhenActiveVariableInCallSignature_ReturnsTrue)
{
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x, double &y)",
        "x",
        "y",
        "tangent",
        "Gradient");
    EXPECT_TRUE(config_file->validateInput());
}

TEST(SimpleConfigFile, ValidateInput_Mode_Tangent)
{
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x, double &y)",
        "x",
        "y",
        "Tangent",
        "Jacobian");
    EXPECT_TRUE(config_file->validateInput());
}

TEST(SimpleConfigFile, ValidateInput_WhenActiveVariableNotInCallSignature_ReturnsFalse)
{
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x, double &y)",
        "active_not_in_call_signature",
        "y",
        "tangent",
        "Jacobian");
    EXPECT_FALSE(config_file->validateInput());
}

TEST(SimpleConfigFile, CreateSimpleConfigFile_WhenInputInConstructor_ReturnsExpectedOutput) {
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
        "void f(double &x, double &y)",
        "x",
        "y",
        "tangent",
        "Jacobian");
    EXPECT_EQ("cpp", config_file->getLanguage());
    std::cout << config_file->getFirstFunction().active << std::endl;
    EXPECT_EQ("x", config_file->getFirstFunction().active);
    EXPECT_EQ("Jacobian", config_file->getFirstFunction().driver_type);
    EXPECT_EQ("tangent", config_file->getFirstFunction().mode);
    EXPECT_EQ("void f(double &x, double &y)", config_file->getFirstFunction().call_signature);
}

TEST(SimpleConfigFile, CreateSimpleConfigFile_WhenMultipleActiveInputs_ReturnsExpectedOutput){
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void f(double &x, double &y)",
                                                          "x",
                                                          "y",
                                                          "tangent",
                                                          "NOT_IMPORTANT");
    EXPECT_EQ("cpp", config_file->getLanguage());
    EXPECT_EQ("x,y", config_file->getFirstFunction().active);
    EXPECT_EQ("tangent", config_file->getFirstFunction().mode);
    EXPECT_EQ("void f(double &x, double &y)", config_file->getFirstFunction().call_signature);
}

TEST(SimpleConfigFile, CreateSimpleConfigFile_WhenOneInputOneOutput_ReturnsExpectedOutput){
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void f(double &x, double &y)",
                                                          "x",
                                                          "y",
                                                          "tangent",
                                                          "jacobian");
    EXPECT_EQ("cpp", config_file->getLanguage());
    EXPECT_EQ("x", config_file->getFirstFunction().active);
    EXPECT_EQ("y", config_file->getFirstFunction().output);
    EXPECT_EQ("jacobian", config_file->getFirstFunction().driver_type);
    EXPECT_EQ("tangent", config_file->getFirstFunction().mode);
    EXPECT_EQ("void f(double &x, double &y)", config_file->getFirstFunction().call_signature);
}
TEST(SimpleConfigFile, Implemented_Vector_Structure_For_Input_and_Output_variables){
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void f(double &x, double &y)",
                                                          "x, a, b",
                                                          "y, z, w",
                                                          "tangent",
                                                          "Gradient");
    EXPECT_EQ("x", config_file->getFirstFunction().activeVec[0]);
    EXPECT_EQ("a", config_file->getFirstFunction().activeVec[1]);
    EXPECT_EQ("b", config_file->getFirstFunction().activeVec[2]);
    EXPECT_EQ("y", config_file->getFirstFunction().outputVec[0]);
    EXPECT_EQ("z", config_file->getFirstFunction().outputVec[1]);
    EXPECT_EQ("w", config_file->getFirstFunction().outputVec[2]);
    
}