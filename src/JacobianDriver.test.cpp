#include <gtest/gtest.h>

#include "JacobianDriver.hpp"
#include "UtilitiesMock.hpp"
#include "ConfigFileMock.hpp"

using ::testing::Return;

TEST(JacobianDriver, CreateDriver_WhenModeTangentInputVectorial_ReturnsJacobianDriver) {
    // Setup
    UtilitiesMock utilitiesMock;
    ConfigFileMock configFileMock;

    EXPECT_CALL(configFileMock, getMode)
            .WillRepeatedly(Return("tangent"));
    EXPECT_CALL(configFileMock, getActiveVariables)
            .WillRepeatedly(Return("x"));
    EXPECT_CALL(configFileMock, getOutputVariables)
            .WillRepeatedly(Return("y"));

    EXPECT_CALL(utilitiesMock, createDriverCallSignature)
            .WillOnce(Return("void f_jacobian(std::vector<double> &x, std::vector<double> &y, std::vector<double> &dy)"));
    EXPECT_CALL(utilitiesMock, initializeSeedValue)
            .WillOnce(Return("std::vector<double> x_t(x.size(), 0.0)"))
            .WillOnce(Return("std::vector<double> y_t(y.size(), 0.0)"));
    EXPECT_CALL(utilitiesMock, setSeedValue)
            .WillOnce(Return("x_t[i] = 1.0"));
    EXPECT_CALL(utilitiesMock, getAssociationByNameSignature)
            .WillOnce(Return("f_t(x, x_t, y, y_t)"));
    EXPECT_CALL(utilitiesMock, harvestVec)
            .WillOnce(Return("dy.insert(dy.end(), y_t.begin(), y_t.end())"));
    EXPECT_CALL(utilitiesMock, resetSeedValue)
            .WillOnce(Return("x_t[i] = 0.0"));
    EXPECT_CALL(utilitiesMock, createLoopSignature)
            .WillOnce(Return("for (size_t i = 0; i < x.size(); ++i)"));

    auto driver = std::make_unique<JacobianDriver>();
    std::vector<std::string> expected = {"void f_jacobian(std::vector<double> &x, std::vector<double> &y, std::vector<double> &dy)",
                                         "std::vector<double> x_t(x.size(), 0.0)",
                                         "std::vector<double> y_t(y.size(), 0.0)",
                                         "for (size_t i = 0; i < x.size(); ++i)",
                                         "x_t[i] = 1.0", 
                                         "f_t(x, x_t, y, y_t)", 
                                         "dy.insert(dy.end(), y_t.begin(), y_t.end())", 
                                         "x_t[i] = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(&utilitiesMock, &configFileMock);

    // Assert
    EXPECT_EQ(expected, strings);
}

TEST(JacobianDriver, CreateDriver_Adjoint_1input_vec_1output_vec) {
    // Setup
    UtilitiesMock utilitiesMock;
    ConfigFileMock configFileMock;

    EXPECT_CALL(configFileMock, getMode)
            .WillRepeatedly(Return("adjoint"));
    EXPECT_CALL(configFileMock, getActiveVariables)
            .WillRepeatedly(Return("x"));
    EXPECT_CALL(configFileMock, getOutputVariables)
            .WillRepeatedly(Return("y"));

    EXPECT_CALL(utilitiesMock, createDriverCallSignature)
            .WillOnce(Return("void f_jacobian(std::vector<double> &x, std::vector<double> &dx, std::vector<double> &y)"));
    EXPECT_CALL(utilitiesMock, initializeSeedValue)
            .WillOnce(Return("std::vector<double> x_a(x.size(), 0.0)"))
            .WillOnce(Return("std::vector<double> y_a(y.size(), 0.0)"));
    EXPECT_CALL(utilitiesMock, setSeedValue)
            .WillOnce(Return("y_a[i] = 1.0"));
    EXPECT_CALL(utilitiesMock, getAssociationByNameSignature)
            .WillOnce(Return("f_a(x, x_a, y, y_a)"));
    EXPECT_CALL(utilitiesMock, harvestVec)
            .WillOnce(Return("dx.insert(dx.end(), x_a.begin(), x_a.end())"));
    EXPECT_CALL(utilitiesMock, resetSeedValue)
            .WillOnce(Return("y_a[i] = 0.0"));
    EXPECT_CALL(utilitiesMock, createLoopSignature)
            .WillOnce(Return("for (size_t i = 0; i < x.size(); ++i)"));

    auto driver = std::make_unique<JacobianDriver>();
    std::vector<std::string> expected = {"void f_jacobian(std::vector<double> &x, std::vector<double> &dx, std::vector<double> &y)",
                                         "std::vector<double> x_a(x.size(), 0.0)",
                                         "std::vector<double> y_a(y.size(), 0.0)",
                                         "for (size_t i = 0; i < x.size(); ++i)",
                                         "y_a[i] = 1.0", 
                                         "f_a(x, x_a, y, y_a)", 
                                         "dx.insert(dx.end(), x_a.begin(), x_a.end())", 
                                         "y_a[i] = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(&utilitiesMock, &configFileMock);

    // Assert
    EXPECT_EQ(expected, strings);
}