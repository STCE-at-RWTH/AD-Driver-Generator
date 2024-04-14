#ifndef SISC_LAB_CPPOUTPUTPARSER_HPP
#define SISC_LAB_CPPOUTPUTPARSER_HPP

#include <iostream>
#include <cassert>

#include <absl/strings/str_cat.h>

#include "OutputParser.hpp"

class CppOutputParser : public OutputParser {
public:
    ~CppOutputParser() override = default;
    void parse(std::pair<std::vector<std::string>, std::vector<int>> &input) final;
};

void CppOutputParser::parse(std::pair<std::vector<std::string>, std::vector<int>> &input) {
    // assert that they are equal in size
    assert(input.first.size() == input.second.size());

    // loop over all input first but compare to the integer which is in input second
    for (size_t i = 0; i < input.first.size()-1; ++i) {
        // indentation based on the indentation level integer counter
        auto indentation = std::string(input.second.at(i),'\t');

        // adding brackets if the levels do change
        if (input.second.at(i+1) > input.second.at(i)) {
            // add opening bracket if next indentation is bigger
            input.first.at(i) = absl::StrCat(indentation, input.first.at(i), "{");
        } else if (input.second.at(i+1) < input.second.at(i)) {
            // add closing bracket if next indentation is smaller
            input.first.at(i) = absl::StrCat(indentation, input.first.at(i), ";}");
        } else {
            // add simple semicolon at end of a line
            input.first.at(i) = absl::StrCat(indentation, input.first.at(i), ";");
        }
        if ((i+1) == input.first.size()-1 && input.second.at(i+1) != 0) {
            // add as many needed closing brackets at the end as needed
            indentation = std::string(input.second.at(i+1),'\t');
            auto closing_brackets = std::string(input.second.at(i+1),'}');
            input.first.at(i+1) = absl::StrCat(indentation,input.first.at(i+1), ";", closing_brackets);
        }
    }
}

#endif //SISC_LAB_CPPOUTPUTPARSER_HPP
