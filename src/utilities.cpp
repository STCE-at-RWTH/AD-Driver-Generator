#include <string>
#include <stdexcept>
#include <vector>

#include "absl/strings/str_split.h"
#include "absl/strings/str_cat.h"
#include "absl/algorithm/container.h"

// std::string setSeedValue(std::string variable, std::string type_of_variable, std::string value_for_seeding)
// {
//     throw std::runtime_error("Not implemented yet");
// }

std::string setSeedValue(const std::string& variable, const std::string& type_of_variable, const std::string& value_for_seeding)
{
    // Check if the type_of_variable is "double" (For simplicity, you can extend this for other types)
    if (type_of_variable != "double") {
        throw std::invalid_argument("Unsupported variable type for seeding.");
    }
    // Construct the seed value assignment string
    std::string seed_assignment = absl::StrCat(type_of_variable, " ", variable, " = ", value_for_seeding);

    return seed_assignment;
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

std::string createLoopSignature(const std::string &activeVariable, int level) {
    // create based on the level a multiplication of i
    char loopVariableChar = 'i';
    std::string loopVariable;
    for (auto i = 0; i < level; ++i){ loopVariable += loopVariableChar; }
    std::string loopSignature = "for (size_t " + loopVariable + " = 0; " + loopVariable + " < " + activeVariable + ".size(); ++" + loopVariable + ")";
    return loopSignature;
}

std::string getAssociationByNameSignatureCompute(const std::string &callSignature, const std::string &activeVariable){
    
    // creates the function call with the _t at the end
    std::vector<std::string> splittedCallSignature = absl::StrSplit(callSignature, absl::ByAnyChar(" ,()"),  absl::SkipEmpty());
    std::string functionCall = absl::StrCat(splittedCallSignature[1], "_t(");

    // separates the arguments from the call signature and organize in a vector
    std::vector<std::string> callSignatureArguments = absl::StrSplit(callSignature, absl::ByAnyChar(",()"),  absl::SkipEmpty());
    callSignatureArguments.erase(callSignatureArguments.begin());

    // creates a vector with the active variables
    std::vector<std::string> activeVariables = absl::StrSplit(activeVariable, absl::ByAnyChar(" ,"),  absl::SkipEmpty());
    std::vector<std::string> words;

    // checks which arguments from call signature are active variables or parameters
    for (int i = 0; i < callSignatureArguments.size(); i++) {
        words = absl::StrSplit(callSignatureArguments[i], absl::ByAnyChar(" &"), absl::SkipEmpty());
        functionCall = absl::StrCat(functionCall, words.back());

        if (absl::c_linear_search(activeVariables, words.back())) {
            functionCall = absl::StrCat(functionCall, ", ", words.back(), "_t");
        }

        if (i < callSignatureArguments.size() - 1) {
            functionCall = absl::StrCat(functionCall, ", ");
        } else {
            functionCall = absl::StrCat(functionCall, ")");
        }
    }   

    return functionCall;
}

std::string createDriverCallSignature(const std::string &callSignature, const std::string &driver_type){
    std::vector<std::string> splittedCallSignature = absl::StrSplit(callSignature, absl::ByAnyChar(" ,()"),  absl::SkipEmpty());
    std::vector<std::string> driverType = absl::StrSplit(driver_type, absl::ByAnyChar(" ,()"),  absl::SkipEmpty());
    std::string driverCallSignature = absl::StrCat(splittedCallSignature[0]," ", splittedCallSignature[1], "_", driverType[0]);  
    return driverCallSignature;
}