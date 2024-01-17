#include "GradientDriver.hpp"
#include "CppUtilities.hpp"
#include "SimpleConfigFile.hpp"
#include "CppOutputParser.hpp"

#include <gtest/gtest.h>

TEST(GradientDriver, Create_Driver_For_Scalar) {
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void f(double &x)",
                                                          "x", "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());

    auto driver = std::make_unique<GradientDriver>();
    auto output = driver->createDriver(cppUtilities.get(), config_file.get());
    auto cppParser = std::make_unique<CppOutputParser>();
    cppParser->parse(output);
    for (auto i : output.first) {
        std::cout << i << std::endl;
    }
}

TEST(GradientDriver, Create_Driver_For_Vector) {
    auto config_file = std::make_unique<SimpleConfigFile>("cpp",
                                                          "void someFunction(std::vector<double> &x)",
                                                          "x", "tangent",
                                                          "gradient");
    auto cppUtilities = std::make_unique<CppUtilities>(config_file->getFirstFunction());

    auto driver = std::make_unique<GradientDriver>();
    auto output = driver->createDriver(cppUtilities.get(), config_file.get());
    auto cppParser = std::make_unique<CppOutputParser>();
    cppParser->parse(output);
    for (auto i : output.first) {
        std::cout << i << std::endl;
    }
}
