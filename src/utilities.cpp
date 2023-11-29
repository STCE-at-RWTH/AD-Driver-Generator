#include <string>
#include <stdexcept>
#include <vector>

#include "absl/strings/str_split.h"

#include "utilities.hpp"

std::string setSeedValue(std::string variable, std::string type_of_variable, std::string value_for_seeding)
{
    throw std::runtime_error("Not implemented yet");
}


std::string getTypeOfVariable(const std::string &callSignature, const std::string &variableName)
{
    // check if the variable name is in the call signature
    try
    {
        if (!(absl::StrContains(callSignature, variableName)))
            throw std::invalid_argument("Variable name not found in call signature: " + variableName);
    } catch (std::invalid_argument &exception)
    {
        throw exception;
    }

    std::vector<std::string> callSignatureSplitted = absl::StrSplit(callSignature, absl::ByAnyChar(" ,("));

    for (auto &i : callSignatureSplitted)
    {
        // do not remove & if it is the only character in the string
        if (i.size() > 1){
            if (absl::StartsWith(i, "&")) {
                i.erase(0, 1);
            }
            if (absl::EndsWith(i, "&")) {
                i.pop_back();
            }
        }

        if (absl::EqualsIgnoreCase(i, variableName)) {
            if (*std::prev(&i) == "&") {
                return *std::prev(&i,2);
            }
            return *std::prev(&i);
        }
    }
}
