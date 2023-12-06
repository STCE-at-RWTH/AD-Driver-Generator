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
    std::vector<std::string> callSignatureSplitted = absl::StrSplit(callSignature, absl::ByAnyChar(" ,("),  absl::SkipEmpty());

    for (auto &i : callSignatureSplitted)
    {
        // do not remove & if it is the only character in the string
        if (i.size() > 1){
            if (absl::StartsWith(i, "&")) {
                i.erase(i.begin());
            }
            if (absl::EndsWith(i, "&")) {
                i.pop_back();
            }
        }

        // use logic that the type needs to be always before the variable name
        if (absl::EqualsIgnoreCase(i, variableName)) {
            if (*std::prev(&i) == "&") {
                return *std::prev(&i,2);
            }
            return *std::prev(&i);
        }
    }
    return "";
}
