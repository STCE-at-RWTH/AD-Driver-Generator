#include <gtest/gtest.h>

#include "DriverFactory.hpp"
#include "ConfigFileMock.hpp"

TEST(DriverFactory, GetDriverType_WhenConfigurationIsGradient_ReturnsNotNull) {
    ConfigFileMock configFileMock;
    EXPECT_CALL(configFileMock, getDriverType())
    .WillRepeatedly(::testing::Return("gradient"));

    auto driver = std::make_unique<DriverFactory>()->getDriverType(&configFileMock);
    EXPECT_TRUE(driver != nullptr);
}

TEST(DriverFactory, GetDriverType_WhenConfigurationIsJacobian_ReturnsNotNull) {
    ConfigFileMock configFileMock;
    EXPECT_CALL(configFileMock, getDriverType())
    .WillRepeatedly(::testing::Return("jacobian"));

    auto driver = std::make_unique<DriverFactory>()->getDriverType(&configFileMock);
    EXPECT_TRUE(driver != nullptr);
}

TEST(DriverFactory, GetDriverType_WhenConfigurationIsNotGradient_StopsExecution) {
    EXPECT_EXIT(
            ConfigFileMock configFileMock;
            EXPECT_CALL(configFileMock, getDriverType()).WillOnce(::testing::Return("INVALID_DRIVER_TYPE"));

            std::make_unique<DriverFactory>()->getDriverType(&configFileMock),
                ::testing::ExitedWithCode(1), "");

}