#include "GradientDriver.hpp"
#include "UtilitiesMock.hpp"
#include "CppUtilities.hpp"
#include "SimpleConfigFile.hpp"
#include "ConfigFileMock.hpp"
#include "CppOutputParser.hpp"

#include <gtest/gtest.h>

using ::testing::Return;

TEST(GradientDriver, With_mocks){
    auto mockUtilities = std::make_unique<UtilitiesMock>();
    auto mockConfigFile = std::make_unique<ConfigFileMock>();

    EXPECT_CALL(*mockUtilities, getAssociationByNameSignature())
    .Times(1)
    .WillRepeatedly(Return("void f(double &x)"));
    EXPECT_CALL(*mockUtilities, getAssociationByNameSignature())
            .Times(1)
            .WillRepeatedly(Return("void f(double &x)"));

    auto driver = std::make_unique<GradientDriver>();
    auto output = driver->createDriver(mockUtilities.get(), mockConfigFile.get());

    std::vector<std::string> expected = {"void f_gradient(double &x, double &dx)\n"
                     "double x_t(0.0)\n"
                     "x_t = 1.0\n"
                     "f_t(x, x_t)\n"
                     "dx = x_t\n"
                     "x_t = 0.0"};

    EXPECT_EQ(output.first, expected);

}

TEST(GradientDriver, Create_Driver_For_Scalar) {
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
                                         "x_t = 1.0",
                                         "f_t(x, x_t, y, y_t)",
                                         "dx = x_t",
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
                                         "y_t = 1.0",
                                         "g_t(y, y_t, z, z_t, p)",
                                         "dy = y_t",
                                         "y_t = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings );
}

TEST(GradientDriver, CreateDriver_WhenInputIsVector_ReturnsExpectedOutput) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void someFunction(std::vector<double> &x, std::vector<double> &y)",
                                                          "x",
                                                          "y",
                                                          "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<GradientDriver>();
    std::vector<std::string> expected = {"void someFunction_gradient(std::vector<double> &x, std::vector<double> &y, std::vector<double> &dy)",
                                         "std::vector<double> x_t(x.size(), 0.0)",
                                         "for (size_t i = 0; i < x.size(); ++i)",
                                         "x_t[i] = 1.0",
                                         "someFunction_t(x, x_t, y, y_t)",
                                         "dx[i] = x_t[i]",
                                         "x_t[i] = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings);
}
