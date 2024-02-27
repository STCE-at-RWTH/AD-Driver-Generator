#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "UtilitiesFactory.hpp"
#include "ConfigFileMock.hpp"

TEST(UtilitiesFactory, GetUtilities_WhenConfigurationIsCpp_ReturnsUtilities) {
    // Arrange
    ConfigFileMock configFileMock;
    auto callSignature = CallSignature("f(const std::vector<double> &x)", "x", "y", "tangent", "jacobian");
    auto callSignatures = std::vector<CallSignature>();
    callSignatures.push_back(callSignature);

    EXPECT_CALL(configFileMock, getLanguage())
            .WillOnce(testing::Return("cpp"));
    EXPECT_CALL(configFileMock, getFunctions())
            .WillOnce(testing::Return(callSignatures));

    // Act
    auto utilities = std::make_unique<UtilitiesFactory>()->getUtilities(&configFileMock);

    // Assert
    EXPECT_TRUE(utilities != nullptr);
}

TEST(UtilitiesFactory, GetUtilities_WhenConfigurationIsInvalid_StopsExecution) {
    EXPECT_EXIT(
            // Arrange
            ConfigFileMock configFileMock;
            EXPECT_CALL(configFileMock, getLanguage())
                    .WillOnce(testing::Return("SOME_UNKNOWN_STRING"));

            // Act
            std::make_unique<UtilitiesFactory>()->getUtilities(&configFileMock),
                ::testing::ExitedWithCode(1), "");
}