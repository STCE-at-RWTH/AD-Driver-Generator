#include "gtest/gtest.h"

// TEST(DualNumber, Addition) {
//   DualNumber<double> x(1, 1);
//   DualNumber<double> y(2, 2);
//   DualNumber<double> z = x + y;
//   EXPECT_EQ(z.value, 3);
//   EXPECT_EQ(z.tangent, 3);
// }

TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
