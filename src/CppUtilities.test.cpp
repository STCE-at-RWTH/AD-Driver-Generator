#include <gtest/gtest.h>

#include "CppUtilities.hpp"
#include "CallSignature.hpp"

TEST(CppUtilities, GetTypeOfVariable_WhenInputDelimitedWithSpace_ReturnsType)
{
  // Setup
  auto mockCallSignature = std::make_unique<CallSignature>("double x", "x", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"double"};

  // Act
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetTypeOfVariable_WhenTwoInputsDelimitedWithComma_ReturnsType)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("double x, double y", "x", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"double"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetTypeOfVariable_WhenBracketsTouchVariable_ReturnsType)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("double (a)", "a", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"double"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetTypeOfVariable_WhenVariableIsPassedByReference_ReturnsType)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("float &a", "a", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"float"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetTypeOfVariable_WhenVariableIsPassedByReferenceWithWhitespace_ReturnsType)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("float & a", "a", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"float"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetTypeOfVariable_WhenVariableIsPassedByReferenceTouchingType_ReturnsType)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("float& a", "a", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"float"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetTypeOfVariable_WhenVariableIsPassedByReferenceTouchingTypeTouchedByBrackets_ReturnsType)
{
  // SETUP
  auto mockCallSignature = std::make_unique<CallSignature>("float& (a)", "a", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
  auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
  std::string expected{"float"};

  // ACT
  auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

  // ASSERT
  EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetTypeOfVariable_WhenTwoVariablesPassedByReference_ReturnsType)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("double &x, float& y", "y", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"float"};

    // ACT
    auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetTypeOfVariable_WhenClosingBracketTouchesVariable_ReturnsType)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("double &x)", "x", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"double"};

    // ACT
    auto actual = cppUtilities->getTypeOfVariable(mockCallSignature->active);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetAssociationByNameSignature_WhenOneActiveInputAndOneActiveOutput_ReturnsAssociationByName)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void f(double &x, double &y, const double p)", "x", "y","tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"f_t(x, x_t, y, y_t, p)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetAssociationByNameSignature_WhenTwoActiveInputs_ReturnsAssociationByName)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void f(double &x, double &y)", "x,y", "NOT_IMPORTANT","tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"f_t(x, x_t, y, y_t)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetAssociationByNameSignature_WhenThreeActiveInputsOneOutputTypeTangent_ReturnsAssociationByName)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void newton(T &x, const PT &p, const PT &w, T &y)", "x, p, w", "y", "tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"newton_t(x, x_t, p, p_t, w, w_t, y, y_t)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetAssociationByNameSignature_WhenThreeActiveInputsOneOutputTypeAdjoint_ReturnsAssociationByName)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void newton(T &x, const PT &p, const PT &w, T &y)", "x, p, w","y", "adjoint", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"newton_a(x, x_a, p, p_a, w, w_a, y, y_a)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetAssociationByNameSignature_WhenOneActiveVectorAsInput_ReturnsAssociationByName)
{
    // SETUP
    auto mockCallSignature = std::make_unique<CallSignature>("void f(std::vector<double> &x)", "x", "NOT_IMPORTANT","tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);
    std::string expected{"f_t(x, x_t)"};

    // ACT
    auto actual = cppUtilities->getAssociationByNameSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateLoopSignature_WhenLoopWithLevel1_ReturnsLoop)
{
    // SETUP
    std::string activeVariable {"x"};
    int level = 1;
    std::string expected{"for (size_t i = 0; i < x.size(); ++i)"};
    auto mockCallSignature = std::make_unique<CallSignature>("NOT_IMPORTANT", "NOT_IMPORTANT", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);

    // ACT
    auto actual = cppUtilities->createLoopSignature(activeVariable, level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateLoopSignature_WhenLoopWithLevel2_ReturnsLoop)
{
    // SETUP
    std::string activeVariable {"x"};
    int level = 2;
    std::string expected{"for (size_t ii = 0; ii < x.size(); ++ii)"};
    auto mockCallSignature = std::make_unique<CallSignature>("NOT_IMPORTANT", "NOT_IMPORTANT", "NOT_IMPORTANT", "NOT_IMPORTANT","NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*mockCallSignature);

    // ACT
    auto actual = cppUtilities->createLoopSignature(activeVariable, level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, SetSeedValue_WhenScalarTypeLoopLevel2ModeTangent_ReturnsScalarString)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("void f(double &x, double &y)", "x", "NOT_IMPORTANT","tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string value_for_seeding = "1.0";
    std::string loop_level = "2";
    std::string expected = "x_t = 1.0";

    // ACT
    auto actual = cppUtilities->setSeedValue(callSignature->active, value_for_seeding, loop_level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, SetSeedValue_WhenVectorTypeLoopLevel2ModeAdjoint_ReturnsVectorString)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("std::vector<double> x", "x", "NOT_IMPORTANT","adjoint", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string value_for_seeding = "1.0";
    std::string loop_level = "2";
    std::string expected = "x_a[ii] = 1.0";

    // ACT
    auto actual = cppUtilities->setSeedValue(callSignature->active, value_for_seeding, loop_level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, InitializeSeedValue_WhenScalarTypeModeTangent_ReturnsScalar)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("f(double x)", "x", "NOT_IMPORTANT","tangent", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string expected = "double x_t(0.0)";

    // ACT
    auto actual = cppUtilities->initializeSeedValue(callSignature->active);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, InitializeSeedValue_WhenVectorTypeModeAdjoint_ReturnsVector)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("void f(std::vector<float> x)", "x", "NOT_IMPORTANT","adjoint", "NOT_IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string expected = "std::vector<float> x_a(x.size(), 0.0)";

    // ACT
    auto actual = cppUtilities->initializeSeedValue(callSignature->active);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, ResetSeedValue_WhenScalarInputModeTangent_ReturnsScalar)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("double x", "x", "NOT_IMPORTANT","tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string loop_level = "2";

    // ACT
    auto actual = cppUtilities->resetSeedValue(callSignature->active, loop_level);

    // ASSERT
    std::string expected = "x_t = 0.0";
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, ResetSeedValue_WhenVectorInputModeAdjoint_ReturnsVector)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("std::vector<double> x", "x", "NOT_IMPORTANT","adjoint", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string loop_level = "2";
    std::string expected = "x_a[ii] = 0.0";

    // ACT
    auto actual = cppUtilities->resetSeedValue(callSignature->active, loop_level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, Harvest_WhenVectorialInputLoopLevel2ModeAdjoint_ReturnsHarvestString)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("std::vector<double> y", "y", "NOT_IMPORTANT","adjoint", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string loop_level = "2";
    std::string expected = "dy[ii] = y_a[ii]";

    // ACT
    auto actual = cppUtilities->harvest(callSignature->active, loop_level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, Harvest_WhenVectorialInputLoopLevel1ModeTangent_ReturnsHarvestString)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("std::vector<double> x", "x", "NOT_IMPORTANT","tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string loop_level = "1";
    std::string expected = "dx[i] = x_t[i]";

    // ACT
    auto actual = cppUtilities->harvest(callSignature->active, loop_level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, Harvest_WhenScalarInputLoopLevel0ModeTangent_ReturnsHarvestString)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("float x", "x", "NOT_IMPORTANT","tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string loop_level = "0";
    std::string expected = "dx = x_t";

    // ACT
    auto actual = cppUtilities->harvest(callSignature->active, loop_level);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, HarvestVec_WhenModeTagentDriverTypeGradient_ReturnsHarvestVecString)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("void f(std::vector<double> x, std::vector<double> y)", "x", "y","tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string expected = "dy.insert(dy.end(), y_t.begin(), y_t.end())";

    // ACT
    auto actual = cppUtilities->harvestVec(callSignature->active,callSignature->output);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, HarvestVec_WhenModeAdjointDriverTypeGradient_ReturnsHarvestVecString)
{
    // SETUP
    auto callSignature = std::make_unique<CallSignature>("void f(std::vector<double> x, std::vector<double> y)", "x", "y","adjoint", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*callSignature);
    std::string expected = "dx.insert(dx.end(), x_a.begin(), x_a.end())";

    // ACT
    auto actual = cppUtilities->harvestVec(callSignature->active,callSignature->output);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateDriverCallSignature_WhenOneActiveDriverTypeGradient_ReturnsDriverCallSignature)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, double &y)", "x", "y","tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"void f_gradient(double &x, double &y, double &dy)"};

    // ACT
    auto actual = cppUtilities->createDriverCallSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateDriverCallSignature_WhenTwoActiveDriverTypeGradient_ReturnsDriverCallSignature)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, double &y)", "x", "y", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"void f_gradient(double &x, double &y, double &dy)"};

    // ACT
    auto actual = cppUtilities->createDriverCallSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateDriverCallSignature_WhenThreeActiveDriverTypeGradient_ReturnsDriverCallSignature)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, double &a, double &y)", "x, a", "y", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"void f_gradient(double &x, double &a, double &y, double &dy)"};

    // ACT
    auto actual = cppUtilities->createDriverCallSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateDriverCallSignature_WhenThreeActiveModeAdjointDriverTypeGradient_ReturnsDriverCallSignature)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, double &a, double &y)", "x, a", "y", "adjoint", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"void f_gradient(double &x, double &dx, double &a, double &da, double &y)"};

    // ACT
    auto actual = cppUtilities->createDriverCallSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateDriverCallSignature_WhenThreeActiveModeTangentDriverTypeJacobian_ReturnsDriverCallSignature)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(std::vector<double> &x, std::vector<double> &a, std::vector<double> &y)", "x, a", "y","tangent", "jacobian");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"void f_jacobian(std::vector<double> &x, std::vector<double> &a, std::vector<double> &y, std::vector<double> &dy)"};

    // ACT
    auto actual = cppUtilities->createDriverCallSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateDriverCallSignature_WhenTwoActiveModeAdjointDriverTypeGradient_ReturnsDriverCallSignature)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, double &y)", "x", "y","adjoint", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"void f_gradient(double &x, double &dx, double &y)"};

    // ACT
    auto actual = cppUtilities->createDriverCallSignature();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateDriverCallArguments_WhenTwoActiveModeTangentDriverTypeGradient_ReturnsDriverCallArguments)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, double &y)", "x", "y","tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"(double &x, double &y, double &dy)"};

    // ACT
    auto actual = cppUtilities->createDriverCallArguments();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateDriverCallArguments_WhenThreeActiveModeTangentDriverTypeGradient_ReturnsDriverCallArguments)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void f(double &x, const double &a, double &b, double &out)", "x, a, b", "out", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"(double &x, const double &a, double &b, double &out, double &dout)"};

    // ACT
    auto actual = cppUtilities->createDriverCallArguments();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, CreateDriverCallArguments_WhenFourActiveModeTangentDriverTypeGradient_ReturnsDriverCallArguments)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("void sigmoid(T &x, const T &p, const T &w, T &out)", "x, p, w", "out", "tangent", "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"(T &x, const T &p, const T &w, T &out, T &dout)"};

    // ACT
    auto actual = cppUtilities->createDriverCallArguments();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetModeTypeSuffix_WhenModeAdjoint_ReturnsSuffix)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("NOT IMPORTANT", "NOT IMPORTANT","NOT_IMPORTANT", "adjoint", "NOT IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"_a"};

    // ACT
    auto actual = cppUtilities->getModeTypeSuffix();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetModeTypeSuffix_WhenModeTangent_ReturnsSuffix)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("NOT IMPORTANT", "NOT IMPORTANT","NOT_IMPORTANT","tangent", "NOT IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);
    std::string expected{"_t"};

    // ACT
    auto actual = cppUtilities->getModeTypeSuffix();

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(CppUtilities, GetModeTypeSuffix_WhenModeInvalid_ThrowsInvalidArgument)
{
    // SETUP
    auto call_signature = std::make_unique<CallSignature>("NOT IMPORTANT", "NOT IMPORTANT", "NOT_IMPORTANT","adgent", "NOT IMPORTANT");
    auto cppUtilities = std::make_unique<CppUtilities>(*call_signature);

    // ACT & ASSERT
    EXPECT_THROW(cppUtilities->getModeTypeSuffix(), std::invalid_argument);
}
