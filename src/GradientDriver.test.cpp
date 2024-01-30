#include "GradientDriver.hpp"
#include "CppUtilities.hpp"
#include "SimpleConfigFile.hpp"
#include "CppOutputParser.hpp"

#include <gtest/gtest.h>

TEST(GradientDriver, CreateDriver_WhenOneActiveVariableIsDouble_ReturnsExpectedOutput) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void f(double &x)",
                                                          "x", "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<GradientDriver>();
    std::vector<std::string> expected = {"void f_gradient(double &x, double &dx)", "double x_t(0.0)", "x_t = 1.0", "f_t(x, x_t)", "dx = x_t", "x_t = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings );
}

TEST(GradientDriver, CreateDriver_WhenPassiveVariableInCallSignature_ReturnsExpectedOutput) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void g(float &y, const double &p)",
                                                          "y", "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<GradientDriver>();
    std::vector<std::string> expected = {"void g_gradient(float &y, float &dy, const double &p)", "float y_t(0.0)", "y_t = 1.0", "g_t(y, y_t, p)", "dy = y_t", "y_t = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings );
}

TEST(GradientDriver, CreateDriver_WhenInputIsVector_ReturnsExpectedOutput) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void someFunction(std::vector<double> &x)",
                                                          "x", "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<GradientDriver>();
    std::vector<std::string> expected = {"void someFunction_gradient(std::vector<double> &x, std::vector<double> &dx)",
                                         "std::vector<double> x_t(x.size(), 0.0)",
                                         "for (size_t i = 0; i < x.size(); ++i)",
                                         "x_t[i] = 1.0",
                                         "someFunction_t(x, x_t)",
                                         "dx[i] = x_t[i]",
                                         "x_t[i] = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings);
}
