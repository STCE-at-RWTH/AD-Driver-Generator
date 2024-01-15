//
// Created by felix on 1/8/24.
//

#include "gtest/gtest.h"
#include "CppOutputParser.hpp"

TEST(CppOutputParser, Assert_When_Size_Of_Input_Not_Equal) {
    // Setup
    std::vector<std::string> inputString{"void f_gradient(double &x, double &dx)",
                                         "x_t = 0"};
    std::vector<int> inputInteger{0};
    auto input = std::make_pair(inputString, inputInteger);
    auto cpp_output_parser = std::make_unique<CppOutputParser>();

    // Act
    EXPECT_ANY_THROW(cpp_output_parser->parse(input));
}

TEST(CppOutputParser, Simple_Parse_Expecting_Opening_Closing_Brackets_And_Semicolon) {
    // Setup
    std::vector<std::string> inputString {"void f_gradient(double &x, double &dx)",
                                          "x_t = 0"};
    std::vector<int> inputInteger{0, 1};
    auto input = std::make_pair(inputString, inputInteger);
    auto cpp_output_parser = std::make_unique<CppOutputParser>();

    // Act
    cpp_output_parser->parse(input);

    // Assert
    auto expected = std::vector<std::string>{"void f_gradient(double &x, double &dx){", "\tx_t = 0;}"};

    ASSERT_EQ(input.first, expected);
}

TEST(CppOutputParser, Test_Gradient_Including_For_Loop){
    // Setup
    std::vector<std::string> inputString {"void f_gradient(std::vector<double> &x, std::vector<double> &dx)",
                                          "std::vector<double> x_t(x.size(), 0.0)",
                                          "for (int i = 0; i < x.size(); ++i)",
                                          "x_t[i] = 1.0",
                                          "f_t(x, x_t)",
                                          "dx[i] = x_t[i]",
                                          "x_t[i] = 0"};
    std::vector<int> inputInteger{0,
                                  1,
                                  1,
                                  2,
                                  2,
                                  2,
                                  2};
    auto input = std::make_pair(inputString, inputInteger);
    auto cpp_output_parser = std::make_unique<CppOutputParser>();

    // Act
    cpp_output_parser->parse(input);

    // Assert
    auto expected = std::vector<std::string>{"void f_gradient(std::vector<double> &x, std::vector<double> &dx){",
                                             "\tstd::vector<double> x_t(x.size(), 0.0);",
                                             "\tfor (int i = 0; i < x.size(); ++i){",
                                             "\t\tx_t[i] = 1.0;",
                                             "\t\tf_t(x, x_t);",
                                             "\t\tdx[i] = x_t[i];",
                                             "\t\tx_t[i] = 0;}}"};
    ASSERT_EQ(input.first, expected);
}

TEST(CppOutputParser, Test_Jacobian_Generation){
  std::vector<std::string> inputString {"void f_jacobian(std::vector<double> &x, matrix_x<double> &J)",
                                        "std::vector<double> x_t(x.size(), 0.0)",
                                        "for (size_t i = 0; i < x.size(); ++i)",
                                        "x_t[i] = 1.0",
                                        "f_t(x, x_t)",
                                        "for (size_t ii = 0; ii < x.size(); ++ii)",
                                        "dx(ii,i) = x_t(ii)",
                                        "x_t[i] = 0"};
  std::vector<int> inputInteger{0,
                                1,
                                1,
                                2,
                                2,
                                2,
                                3,
                                2};

  auto input = std::make_pair(inputString, inputInteger);
  auto cpp_output_parser = std::make_unique<CppOutputParser>();

  // Act
  cpp_output_parser->parse(input);

  // Assert
  auto expected = std::vector<std::string>{"void f_jacobian(std::vector<double> &x, matrix_x<double> &J){",
                                        "\tstd::vector<double> x_t(x.size(), 0.0);",
                                        "\tfor (size_t i = 0; i < x.size(); ++i){",
                                        "\t\tx_t[i] = 1.0;",
                                        "\t\tf_t(x, x_t);",
                                        "\t\tfor (size_t ii = 0; ii < x.size(); ++ii){",
                                        "\t\t\tdx(ii,i) = x_t(ii);}",
                                        "\t\tx_t[i] = 0;}}"};
}
