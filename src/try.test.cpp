#include "gtest/gtest.h"
#include "try.hpp"

TEST(DualNumber, Overload_of_addition_value) {
    DualNumber<double> x(1, 1);
    x.value += 1;
    EXPECT_EQ(x.value, 2);
    EXPECT_NE(x.value, 1);
}

TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
