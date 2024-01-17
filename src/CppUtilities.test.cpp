#include "gtest/gtest.h"
#include "CppUtilities.hpp"

TEST(GetTypeOfVariable, Input_With_Space_Delimiter)
{
  // Setup
  auto mockCallSignature = std::make_unique<CallSignature>("double x", "x", "NOT_IMPORTANT", "NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"double"};

  // Act
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Input_With_Two_Variables_Separated_By_Comma)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("double x, double y", "x", "NOT_IMPORTANT", "NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"double"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Bracket_Touches_The_Type)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("double (a)", "a", "NOT_IMPORTANT", "NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"double"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Variable_Passed_By_Reference)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("float &a", "a", "NOT_IMPORTANT", "NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"float"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Variable_Passed_By_Reference_Whitespaces_Separated)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("float & a", "a", "NOT_IMPORTANT", "NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"float"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Variable_Passed_By_Reference_Touching_Type)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("float& a", "a", "NOT_IMPORTANT", "NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"float"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Variable_Passed_By_Reference_Touching_Type_With_Brackets)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("float& (a)", "a", "NOT_IMPORTANT", "NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"float"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Two_Variables_And_Bracket)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("double &x, float& y", "y", "NOT_IMPORTANT", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"float"};

    // ACT
    auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, Bracket_Touching_Variable)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("double &x)", "x", "NOT_IMPORTANT", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"double"};

    // ACT
    auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameSignature, OneVariableOneParameter)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void f(double &x, const double p)", "x", "tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"f_t(x, x_t, p)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameSignature, TwoVariables)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void f(double &x, double &y)", "x,y", "tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"f_t(x, x_t, y, y_t)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameSignature, NewtonGradientTangent)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void newton(T &x, const PT &p, const PT &w)", "x, p, w", "tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"newton_t(x, x_t, p, p_t, w, w_t)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameSignature, NewtonGradientAdjoint)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void newton(T &x, const PT &p, const PT &w)", "x, p, w", "adjoint", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"newton_a(x, x_a, p, p_a, w, w_a)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameSignature, TwoVariablesOneParameter)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void f(double &x, double &y, const double p)", "x, y", "tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"f_t(x, x_t, y, y_t, p)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetAssociationByNameSignature, VectorVariable)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void f(std::vector<double> &x)", "x", "tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"f_t(x, x_t)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateLoopSignature, Loop_with_level_1)
{
    // SETUP
    std::string activeVariable {"x"};
    int level = 1;
    std::string expected{"for (size_t i = 0; i < x.size(); ++i)"};
    auto mockCallSignature = std::make_unique<CallSignature>("NOT_IMPORTANT", "NOT_IMPORTANT", "NOT_IMPORTANT", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);

    // ACT
    auto actual = cppUtilities->createLoopSignature(activeVariable, level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateLoopSignature, Loop_with_level_2)
{
    // SETUP
    std::string activeVariable {"x"};
    int level = 2;
    std::string expected{"for (size_t ii = 0; ii < x.size(); ++ii)"};
    auto mockCallSignature = std::make_unique<CallSignature>("NOT_IMPORTANT", "NOT_IMPORTANT", "NOT_IMPORTANT", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);

    // ACT
    auto actual = cppUtilities->createLoopSignature(activeVariable, level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(SetSeedValue, Tangent_Scalar_Type)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("double x", "x", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string value_for_seeding = "1.0";
    std::string loop_level = "2";
    std::string expected = "x_t = 1.0";

    // ACT
    auto actual = cppUtilities->setSeedValue(callSignature->active, value_for_seeding, loop_level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(SetSeedValue, Adjoint_Vector_Level2_Type)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("std::vector<double> x", "x", "adjoint", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string value_for_seeding = "1.0";
    std::string loop_level = "2";
    std::string expected = "x_a[ii] = 1.0";

    // ACT
    auto actual = cppUtilities->setSeedValue(callSignature->active, value_for_seeding, loop_level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(InitializeSeedValue, DoubleTangentScalar)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("f(double x)", "x", "tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string expected = "double x_t(0.0)";

    // ACT
    auto actual = cppUtilities->initializeSeedValue(callSignature->active);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(InitializeSeedValue, FloatAdjointVector)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("void f(std::vector<float> x)", "x", "adjoint", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string expected = "std::vector<float> x_a(x.size(), 0.0)";

    // ACT
    auto actual = cppUtilities->initializeSeedValue(callSignature->active);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(ResetSeedValue, Tangent_Scalar_Type)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("double x", "x", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string loop_level = "2";

    // ACT
    auto actual = cppUtilities->resetSeedValue(callSignature->active, loop_level);

    // ASSERT
    std::string expected = "x_t = 0.0";
    EXPECT_EQ(actual, expected);
}

TEST(ResetSeedValue, Adjoint_Vector_Level2_Type)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("std::vector<double> x", "x", "adjoint", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string loop_level = "2";
    std::string expected = "x_a[ii] = 0.0";

    // ACT
    auto actual = cppUtilities->resetSeedValue(callSignature->active, loop_level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateDriverCallSignature, Gradient_Driver){
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, double &y)", "x, y", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"void f_gradient(double &x, double &dx, double &y, double &dy)"};

    // ACT
    auto actual = cppUtilities->createDriverCallSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateDriverCallSignature, Sigmoid_Gradient_Driver){
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void sigmoid(double &x, double &y)", "x", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"void sigmoid_gradient(double &x, std::vector<double> &dx, double &y)"};

    // ACT
    auto actual = cppUtilities->createDriverCallSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateDriverCallSignature, Jacobian_Driver){
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(std::vector<double> &x)", "x", "tangent", "jacobian");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"void f_jacobian(std::vector<double> &x, std::vector<std::vector<double>> &dx)"};

    // ACT
    auto actual = cppUtilities->createDriverCallSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);    
}

TEST(CreateDriverCallArguments, Gradient_Driver_Two_Variables){
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, double &y)", "x, y", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"(double &x, double &dx, double &y, double &dy)"};

    // ACT
    auto actual = cppUtilities->createDriverCallArguments();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateDriverCallArguments, Gradient_Driver_Three_Variables){
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, const double &y, double &z)", "x, y, z", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"(double &x, double &dx, const double &y, const double &dy, double &z, double &dz)"};

    // ACT
    auto actual = cppUtilities->createDriverCallArguments();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CreateDriverCallArguments, Gradient_Driver_Sigmoid){
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void sigmoid(T &x, const T &p, const T &w)", "x, p, w", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"(T &x, T &dx, const T &p, const T &dp, const T &w, const T &dw)"};

    // ACT
    auto actual = cppUtilities->createDriverCallArguments();

    // ASSERT
    EXPECT_EQ(actual, expected);
}