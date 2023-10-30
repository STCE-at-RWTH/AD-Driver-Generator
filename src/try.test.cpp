#include "gtest/gtest.h"
#include "try.cpp"

TEST(DualNumber, Addition) {
    DualNumber<double> x(1, 1);
    DualNumber<double> y(2, 2);
    DualNumber<double> z = x + y;
    EXPECT_EQ(z.value, 3);
    EXPECT_EQ(z.tangent, 3);
}