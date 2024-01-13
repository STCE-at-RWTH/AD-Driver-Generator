#include "gtest/gtest.h"

#include "Utilities.hpp"

TEST(InitializeSeedValue, DoubleTangentScalar)
{
    std::string variable = "x";
    std::string type_of_variable = "double";
    std::string mode = "tangent";
    
    std::string expected = "double x_t(0.0)";
    std::string actual = initializeSeedValue(variable, type_of_variable, mode);
    EXPECT_EQ(actual, expected);
}
TEST(InitializeSeedValue, FloatAdjointVector)
{
    std::string variable = "x";
    std::string type_of_variable = "std::vector<float>";
    std::string mode = "adjoint";
    
    std::string expected = "std::vector<float> x_a(x.size(),0.0)";
    std::string actual = initializeSeedValue(variable, type_of_variable, mode);
    EXPECT_EQ(actual, expected);
}
TEST(SetSeedValue, Tangent_Scalar_Type)
{
    std::string variable = "x";
    std::string mood = "tangent";
    std::string output_type = "scalar";
    std::string value_for_seeding = "1.0";
    std::string loop_level = "2";
    std::string expected = "x_t = 1.0";
    std::string actual = setSeedValue(variable, mood, output_type, value_for_seeding, loop_level);
    EXPECT_EQ(actual, expected);
}

TEST(SetSeedValue, Adjoint_Vector_Level2_Type)
{
    std::string variable = "x";
    std::string mood = "adjoint";
    std::string output_type = "vector";
    std::string value_for_seeding = "1.0";
    std::string loop_level = "2";
    std::string expected = "x_a[ii] = 1.0";
    std::string actual = setSeedValue(variable, mood, output_type, value_for_seeding, loop_level);
    EXPECT_EQ(actual, expected);
}

TEST(ResetSeedValue, Tangent_Scalar_Type)
{
    std::string variable = "x";
    std::string mood = "tangent";
    std::string output_type = "scalar";
    std::string loop_level = "2";
    std::string expected = "x_t = 0.0";
    std::string actual = resetSeedValue(variable, mood, output_type, loop_level);
    EXPECT_EQ(actual, expected);
}

TEST(ResetSeedValue, Adjoint_Vector_Level2_Type)
{
    std::string variable = "x";
    std::string mood = "adjoint";
    std::string output_type = "vector";
    std::string loop_level = "2";
    std::string expected = "x_a[ii] = 0.0";
    std::string actual = resetSeedValue(variable, mood, output_type, loop_level);
    EXPECT_EQ(actual, expected);
}



TEST(SetSeedValueOld, VariableFloatType)
{
    std::string variable = "x";
    std::string type_of_variable = "float";
    std::string value_for_seeding = "1.0";
    std::string expected = "float x = 1.0";
    std::string actual = setSeedValue_old(variable, type_of_variable, value_for_seeding);
    EXPECT_EQ(actual, expected);
}
TEST(SetSeedValueOld, VariableDoubleType)
{
    std::string variable = "t";
    std::string type_of_variable = "double";
    std::string value_for_seeding = "1.0";
    std::string expected = "double t = 1.0";
    std::string actual = setSeedValue_old(variable, type_of_variable, value_for_seeding);
    EXPECT_EQ(actual, expected);
}

TEST(SetSeedValueOld, VariableIntType)
{
    std::string variable = "b";
    std::string type_of_variable = "int";
    std::string value_for_seeding = "1.0";
    std::string expected = "int b = 1.0";
    std::string actual = setSeedValue_old(variable, type_of_variable, value_for_seeding);
    EXPECT_EQ(actual, expected);
}

TEST(SetSeedValueOld, VariableInvalidType)
{
    // Test case for an invalid scenario where an inappropriate type is given
    std::string variable = "b";
    std::string type_of_variable = "invalid_type";  // Set an invalid type
    std::string value_for_seeding = "1.0";

    // Use EXPECT_THROW to check if the function throws an exception
    EXPECT_THROW(
        {
            try
            {
                setSeedValue_old(variable, type_of_variable, value_for_seeding);
            }
            catch (const std::invalid_argument& e)
            {
                // Check if the exception message contains the expected error message
                EXPECT_STRCASEEQ(e.what(), "Unsupported variable type for seeding. Allowed types are: int, double, float");
                return;
            }
            FAIL() << "Expected std::invalid_argument not thrown.";
        },
        std::invalid_argument);
}
TEST(SetSeedValueOld, VariableDoubleTypeMultipleVariables)
{
    // Test case for multiple variables
    std::string variable = "t, y, z";
    std::string type_of_variable = "double";
    std::string value_for_seeding = "1.0";
    std::string expected = "double t = 1.0\ndouble y = 1.0\ndouble z = 1.0";
    std::string actual = setSeedValue_old(variable, type_of_variable, value_for_seeding);
    EXPECT_EQ(actual, expected);
}

TEST(SetSeedValueOld, VariableDoubleTypeMultipleVariablesTrimmedWhitespace)
{
    // Test case for multiple variables with leading/trailing whitespace
    std::string variable = " t, y ,z ";
    std::string type_of_variable = "double";
    std::string value_for_seeding = "1.0";
    std::string expected = "double t = 1.0\ndouble y = 1.0\ndouble z = 1.0";
    std::string actual = setSeedValue_old(variable, type_of_variable, value_for_seeding);
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