#include "gtest/gtest.h"
#include "utilities.hpp"

TEST(SetSeedValue, BasicInput) {
    std::string variable = "x";
    std::string type_of_variable = "double";
    std::string value_for_seeding = "1.0";
    std::string expected = "double x = 1.0";
    std::string actual = setSeedValue(variable, type_of_variable, value_for_seeding);
    EXPECT_EQ(actual, expected);
}