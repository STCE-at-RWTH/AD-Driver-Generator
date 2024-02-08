#include "JacobianDriver.hpp"
#include "CppUtilities.hpp"
#include "SimpleConfigFile.hpp"
#include "CppOutputParser.hpp"

#include <gtest/gtest.h>

TEST(JacobianDriver, CreateDriver_Tangent_1input_vec_1output_vec) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void f(std::vector<double> &x, std::vector<double> &y)",
                                                          "x",
                                                          "y",
                                                          "tangent",
                                                          "jacobian");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
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
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings);
}

TEST(JacobianDriver, CreateDriver_Adjoint_1input_vec_1output_vec) {
    // Setup
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void f(std::vector<double> &x, std::vector<double> &y)",
                                                          "x",
                                                          "y",
                                                          "adjoint",
                                                          "jacobian");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());
    auto driver = std::make_unique<JacobianDriver>();
    std::vector<std::string> expected = {"void f_jacobian(std::vector<double> &x,std::vector<double> &dx, std::vector<double> &y)", 
                                         "std::vector<double> x_a(x.size(), 0.0)",
                                         "std::vector<double> y_a(y.size(), 0.0)",
                                         "for (size_t i = 0; i < x.size(); ++i)",
                                         "y_a[i] = 1.0", 
                                         "f_a(x, x_a, y, y_a)", 
                                         "dx.insert(dx.end(), x_a.begin(), x_a.end())", 
                                         "y_a[i] = 0.0"};

    // Act
    auto [strings, level] = driver->createDriver(cppUtilities.get(), config_file.get());

    // Assert
    EXPECT_EQ(expected, strings);
}