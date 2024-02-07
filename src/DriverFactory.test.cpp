#include "gtest/gtest.h"
#include "DriverFactory.hpp"
#include "SimpleConfigFile.hpp"

TEST(DriverFactory, GetDriverType_WhenConfigurationIsGradient_ReturnsNotNull) {
    auto configFile = std::make_unique<SimpleConfigFile>("NOT_IMPORTANT",
                                                          "NOT_IMPORTANT",
                                                          "NOT_IMPORTANT",
                                                          "NOT_IMPORTANT",
                                                          "NOT_IMPORTANT",
                                                          "gradient");

    auto driver = std::make_unique<DriverFactory>()->getDriverType(configFile.get());
    EXPECT_TRUE(driver != nullptr);
}

TEST(DriverFactory, GetDriverType_WhenConfigurationIsNotGradient_StopsExecution) {
    auto configFile = std::make_unique<SimpleConfigFile>("NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_VALID");

    EXPECT_EXIT(std::make_unique<DriverFactory>()->getDriverType(configFile.get()),
                ::testing::ExitedWithCode(1), "");

}