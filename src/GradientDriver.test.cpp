#include "GradientDriver.hpp"
#include "CppUtilities.hpp"
#include "SimpleConfigFile.hpp"
#include "CppOutputParser.hpp"

#include <gtest/gtest.h>

TEST(GradientDriver, CreateDriver_WhenOneActiveVariableIsDouble_ReturnsExpectedOutput) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void f(double &x, double &y)",
                                                          "x",
                                                          "y",
                                                          "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<GradientDriver>();
    std::vector<std::string> expected = {"void f_gradient(double &x, double &y, double &dy)",
                                         "double x_t(0.0)",
                                         "double y_t(0.0)",
                                         "x_t = 1.0",
                                         "f_t(x, x_t, y, y_t)",
                                         "dy = y_t",
                                         "x_t = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings);
}

TEST(GradientDriver, CreateDriver_WhenPassiveVariableInCallSignature_ReturnsExpectedOutput) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void g(float &y, float &z, const double &p)",
                                                          "y",
                                                          "z",
                                                          "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<GradientDriver>();
    std::vector<std::string> expected = {"void g_gradient(float &y, float &z, float &dz, const double &p)",
                                         "float y_t(0.0)",
                                         "float z_t(0.0)",
                                         "y_t = 1.0",
                                         "g_t(y, y_t, z, z_t, p)",
                                         "dz = z_t",
                                         "y_t = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings );
}

TEST(GradientDriver, CreateDriver_WhenInputIsScalar_ReturnsExpectedOutput) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void someFunction(double &x, std::vector<double> &y)",
                                                          "x",
                                                          "y",
                                                          "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<GradientDriver>();
    std::vector<std::string> expected = {"void someFunction_gradient(double &x, std::vector<double> &y, std::vector<double> &dy)",
                                         "double x_t(0.0)",
                                         "std::vector<double> y_t(y.size(), 0.0)",
                                         "for (size_t i = 0; i < y.size(); ++i)",
                                         "x_t = 1.0",
                                         "someFunction_t(x, x_t, y, y_t)",
                                         "dy[i] = y_t[i]",
                                         "x_t = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings);
}



TEST(GradientDriver, CreateDriver_WhenInputIsVector_ReturnsExpectedOutput) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void someFunction(std::vector<double> &x, double &y)",
                                                          "x",
                                                          "y",
                                                          "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<GradientDriver>();
    std::vector<std::string> expected = {"void someFunction_gradient(std::vector<double> &x, double &y,  std::vector<double> &dy)",
                                         "std::vector<double> x_t(x.size(), 0.0)",
                                         "double y_t(0.0)",
                                         "for (size_t i = 0; i < x.size(); ++i)",
                                         "x_t[i] = 1.0",
                                         "someFunction_t(x, x_t, y, y_t)",
                                         "dy[i] = y_t",
                                         "x_t[i] = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings);
}

TEST(GradientDriver, CreateDriver_WhenInputIsVector_Adjoint) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void someFunction(std::vector<double> &x, double &y)",
                                                          "x",
                                                          "y",
                                                          "adjoint",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<GradientDriver>();
    std::vector<std::string> expected = {"void someFunction_gradient(std::vector<double> &x, std::vector<double> &dx, double &y)",
                                         "std::vector<double> x_a(x.size(), 0.0)",
                                         "double y_a(0.0)",
                                         "for (size_t i = 0; i < x.size(); ++i)",
                                         "y_a = 1.0",
                                         "someFunction_a(x, x_a, y, y_a)",
                                         "dx[i] = x_a[i]",
                                         "y_a = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings);
}


//(absl::StrContains(configFile->getActiveVariables() , "std::vector") ) || (absl::StrContains(configFile->getOutputVariables(), "std::vector"))