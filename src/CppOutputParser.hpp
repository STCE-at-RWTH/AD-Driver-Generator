#ifndef SISC_LAB_CPPOUTPUTPARSER_HPP
#define SISC_LAB_CPPOUTPUTPARSER_HPP

#include <iostream>
#include "OutputParser.hpp"
#include "absl/strings/str_cat.h"

class CppOutputParser : public OutputParser {
public:
    ~CppOutputParser() override = default;
    void parse(std::pair<std::vector<std::string>, std::vector<int>> &input) final;
};

void CppOutputParser::parse(std::pair<std::vector<std::string>, std::vector<int>> &input) {
    // assert that they are equal in size
    assert(input.first.size() == input.second.size());

    // loop over all input first but compare to the integer which is in input second
    for (size_t i = 0; i < input.first.size(); ++i) {
        // indentation based on the indentaion level integer counter
        auto indentation = std::string(input.second[i],'\t');

        // adding brackets if the levels do change
        if (input.second[i+1] > input.second[i]) {
            // add opening bracket if next indentation is bigger
            input.first[i] = absl::StrCat(indentation, input.first[i], "{");
        } else if (input.second[i+1] < input.second[i]) {
            // add closing bracket if next indentation is smaller
            input.first[i] = absl::StrCat(indentation, input.first[i], ";}");
        } else {
            // add simple semicolon at end of a line
            input.first[i] = absl::StrCat(indentation, input.first[i], ";");
        }

        if (i == input.first.size()-1 && input.second[i] != 1) {
            // add as many needed closing brackets at the end as needed
            auto closing_brackets = std::string(input.second[i]-1,'}');
            input.first[i] = absl::StrCat(input.first[i], closing_brackets);
        }
    }
}

#endif //SISC_LAB_CPPOUTPUTPARSER_HPP
