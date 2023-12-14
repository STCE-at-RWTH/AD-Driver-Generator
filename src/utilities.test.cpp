#include "gtest/gtest.h"

#include "utilities.hpp"

TEST(SetSeedValue, BasicInput)
{
    std::string variable = "x";
    std::string type_of_variable = "double";
    std::string value_for_seeding = "1.0";
    std::string expected = "double x = 1.0";
    std::string actual = setSeedValue(variable, type_of_variable, value_for_seeding);
    // expect that setSeedvalue throws not implemented
    EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Input_With_Space_Delimiter)
{
    // SETUP
    std::string signature{"double x"};
    std::string active_variable{"x"};
    std::string expected{"double"};

    // ACT
    auto actual = getTypeOfVariable(signature, active_variable);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Input_With_Two_Variables_Separated_By_Comma)
{
    // SETUP
    std::string signature{"double x, double y"};
    std::string active_variable{"x"};
    std::string expected{"double"};

    // ACT
    auto actual = getTypeOfVariable(signature, active_variable);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Bracket_Touches_The_Type)
{
    // SETUP
    std::string signature{"(double a"};
    std::string active_variable{"a"};
    std::string expected{"double"};

    // ACT
    auto actual = getTypeOfVariable(signature, active_variable);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Variable_Passed_By_Reference)
{
    // SETUP
    std::string signature{"float &a"};
    std::string active_variable{"a"};
    std::string expected{"float"};

    // ACT
    auto actual = getTypeOfVariable(signature, active_variable);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Variable_Passed_By_Reference_Whitespaces_Separated)
{
    // SETUP
    std::string signature{"float & a"};
    std::string active_variable{"a"};
    std::string expected{"float"};

    // ACT
    auto actual = getTypeOfVariable(signature, active_variable);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Variable_Passed_By_Reference_Touching_Type)
{
    // SETUP
    std::string signature{"float& a"};
    std::string active_variable{"a"};
    std::string expected{"float"};

    // ACT
    auto actual = getTypeOfVariable(signature, active_variable);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Variable_Passed_By_Reference_Touching_Type_With_Brackets)
{
    // SETUP
    std::string signature{"f(float& a"};
    std::string active_variable{"a"};
    std::string expected{"float"};

    // ACT
    auto actual = getTypeOfVariable(signature, active_variable);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateLoopSignature, Loop_with_level_1)
{
    // SETUP
    std::string activeVariable {"x"};
    int level = 1;
    std::string expected{"for (size_t i = 0; i < x.size(); ++i)"};

    // ACT
    std::string actual = createLoopSignature(activeVariable, level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateLoopSignature, Loop_with_level_2)
{
    // SETUP
    std::string activeVariable {"x"};
    int level = 2;
    std::string expected{"for (size_t ii = 0; ii < x.size(); ++ii)"};

    // ACT
    std::string actual = createLoopSignature(activeVariable, level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameComputeSignature, OneVariableOneParameter){
    // SETUP
    std::string call_signature{"void f(double &x, const double p)"};
    std::string active_variables{"x"};
    std::string expected{"f_t(x, x_t, p)"};
    
    // ACT
    auto actual = getAssociationByNameSignatureCompute(call_signature, active_variables);
    
    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameComputeSignature, TwoVariables){
    // SETUP
    std::string call_signature{"void f(double &x, double &y)"};
    std::string active_variables{"x, y"};
    std::string expected{"f_t(x, x_t, y, y_t)"};
    
    // ACT
    auto actual = getAssociationByNameSignatureCompute(call_signature, active_variables);
    
    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameComputeSignature, TwoVariablesOneParameter){
    // SETUP
    std::string call_signature{"void f(double &x, double &y, const double p)"};
    std::string active_variables{"x, y"};
    std::string expected{"f_t(x, x_t, y, y_t, p)"};
    
    // ACT
    auto actual = getAssociationByNameSignatureCompute(call_signature, active_variables);
    
    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameComputeSignature, VectorVariable){
    // SETUP
    std::string call_signature{"void f(std::vector<double> &x)"};
    std::string active_variables{"x"};
    std::string expected{"f_t(x, x_t)"};
    
    // ACT
    auto actual = getAssociationByNameSignatureCompute(call_signature, active_variables);
    
    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateDriverCallSignature, GradientDriver){
    // SETUP
    std::string call_signature{"void f(double &x, double &y)"};
    std::string driver_type{"gradient"};
    std::string expected{"void f_gradient"};
    
    // ACT
    auto actual = createDriverCallSignature(call_signature, driver_type);
    
    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateDriverCallSignature, JacobianDriver){
    // SETUP
    std::string call_signature{"void fxfts(double &x, double &y)"};
    std::string driver_type{"jacobian"};
    std::string expected{"void fxfts_jacobian"};
    
    // ACT
    auto actual = createDriverCallSignature(call_signature, driver_type);
    
    // ASSERT
    EXPECT_EQ(actual, expected);
}