#include <gtest/gtest.h>

#include "GradientDriver.hpp"
#include "UtilitiesMock.hpp"
#include "ConfigFileMock.hpp"

using ::testing::Return;

TEST(GradientDriver, CreateDriver_WhenScalarVariableModeTangent_ReturnsGradientDriver) {
    // Arrange
    UtilitiesMock utilitiesMock;
    ConfigFileMock configFileMock;
    EXPECT_CALL(configFileMock, getActiveVariables)
            .WillRepeatedly(Return("x"));

    EXPECT_CALL(utilitiesMock, createDriverCallSignature)
            .WillOnce(Return("void f_gradient(double &x, double &dx)"));
    EXPECT_CALL(utilitiesMock, initializeSeedValue)
            .WillOnce(Return("double x_t(0.0)"));
    EXPECT_CALL(utilitiesMock, setSeedValue)
            .WillOnce(Return("x_t = 1.0"));
    EXPECT_CALL(utilitiesMock, getAssociationByNameSignature)
            .WillOnce(Return("f_t(x, x_t)"));
    EXPECT_CALL(utilitiesMock, harvest)
            .WillOnce(Return("dx = x_t"));
    EXPECT_CALL(utilitiesMock, resetSeedValue)
            .WillOnce(Return("x_t = 0.0"));

    auto driver = std::make_unique<GradientDriver>();

    std::vector<std::string> expected = {
        "void f_gradient(double &x, double &dx)",
        "double x_t(0.0)",
        "x_t = 1.0",
        "f_t(x, x_t)",
        "dx = x_t",
        "x_t = 0.0"
    };

    // Act
    auto [strings, levels] = driver->createDriver(&utilitiesMock, &configFileMock);

    // Assert
    EXPECT_EQ(strings, expected);
}

TEST(GradientDriver, CreateDriver_WhenInputIsVector_ReturnsExpectedOutput) {
    // Setup
    UtilitiesMock utilitiesMock;
    ConfigFileMock configFileMock;
    EXPECT_CALL(configFileMock, getActiveVariables)
            .WillRepeatedly(Return("x"));

    EXPECT_CALL(utilitiesMock, createDriverCallSignature)
            .WillOnce(Return("void someFunction_gradient(std::vector<double> &x, std::vector<double> &y, std::vector<double> &dy)"));
    EXPECT_CALL(utilitiesMock, initializeSeedValue)
            .WillOnce(Return("std::vector<double> x_t(x.size(), 0.0)"));
    EXPECT_CALL(utilitiesMock, setSeedValue)
            .WillOnce(Return("x_t[i] = 1.0"));
    EXPECT_CALL(utilitiesMock, getAssociationByNameSignature)
            .WillOnce(Return("someFunction_t(x, x_t, y, y_t)"));
    EXPECT_CALL(utilitiesMock, harvest)
            .WillOnce(Return("dx[i] = x_t[i]"));
    EXPECT_CALL(utilitiesMock, resetSeedValue)
            .WillOnce(Return("x_t[i] = 0.0"));
    EXPECT_CALL(utilitiesMock, createLoopSignature)
            .WillOnce(Return("for (size_t i = 0; i < x.size(); ++i)"));

    auto driver = std::make_unique<GradientDriver>();

    std::vector<std::string> expected = {
        "void someFunction_gradient(std::vector<double> &x, std::vector<double> &y, std::vector<double> &dy)",
        "std::vector<double> x_t(x.size(), 0.0)",
        "for (size_t i = 0; i < x.size(); ++i)",
        "x_t[i] = 1.0",
        "someFunction_t(x, x_t, y, y_t)",
        "dx[i] = x_t[i]",
        "x_t[i] = 0.0"
    };

    // Act
    auto [strings, level] = driver->createDriver(&utilitiesMock, &configFileMock);

    // Assert
    EXPECT_EQ(expected, strings);
}
