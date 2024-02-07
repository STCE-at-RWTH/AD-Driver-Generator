#include "gtest/gtest.h"
#include "UtilitiesFactory.hpp"
#include "SimpleConfigFile.hpp"

TEST(UtilitiesFactory, GetUtilities_WhenConfigurationIsCpp_ReturnsNotNull) {
    auto configFile = std::make_unique<SimpleConfigFile>("cpp",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT");

    auto utilities = std::make_unique<UtilitiesFactory>()->getUtilities(configFile.get());
    EXPECT_TRUE(utilities != nullptr);
}

TEST(UtilitiesFactory, GetUtilities_WhenConfigurationIsInvalid_StopsExecution) {
    auto configFile = std::make_unique<SimpleConfigFile>("Some_Random_Language",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT",
                                                         "NOT_IMPORTANT");

    EXPECT_EXIT(std::make_unique<UtilitiesFactory>()->getUtilities(configFile.get()),
                ::testing::ExitedWithCode(1), "");
}

