#include "gtest/gtest.h"
#include "utilities.hpp"

TEST(SetSeedValue, BasicInput)
{
    std::string variable = "x";
    std::string type_of_variable = "double";
    std::string value_for_seeding = "1.0";
    std::string expected = "double x = 1.0";
    std::string actual = setSeedValue(variable, type_of_variable, value_for_seeding);
    EXPECT_EQ(actual, expected);
}

TEST(SplitString, WhiteSpace_as_delimiter)
{
    // SETUP
    std::string inputString{"abc def"};
    char delimiter{' '};
    auto some_test = " ";
    std::vector<std::string> expected{"abc", "def"};

    // ACT
    auto actual = splitString(inputString, delimiter);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(SplitString, Split_at_commata)
{
    // SETUP
    std::string inputString{"abc,def"};
    char delimiter{','};
    std::vector<std::string> expected{"abc", "def"};

    // ACT
    auto actual = splitString(inputString, delimiter);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(SplitString, Delimiter_not_in_string)
{
    // SETUP
    std::string inputString{"abcdef"};
    char delimiter{' '};
    std::vector<std::string> expected{"abcdef"};

    // ACT
    auto actual = splitString(inputString, delimiter);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(SplitString, WhiteSpace_and_Brackets)
{
    // SETUP
    std::string inputString{"(abc def"};
    std::string delimiter{'(', ' '};

    std::vector<std::string> expected{"abc", "def"};
    std::vector<std::string> actual;
    // ACT
    for (auto delim : delimiter)
        actual = splitString(inputString, delim);

    // ASSERT
    EXPECT_EQ(actual, expected);
}

TEST(GetTypeOfVariable, SimpleInput_with_space_delimiter)
{
    // SETUP
    std::string signature{"double x"};
    std::string active_variable{"x"};
    std::string expected{"double"};

    // ACT
    auto actual = getTypeOfVariable(signature, active_variable);

    // ASSERT
    EXPECT_EQ(actual, expected);
}
