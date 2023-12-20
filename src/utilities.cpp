#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>  // For std::stringstream

#include "absl/strings/str_split.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_join.h"
#include "absl/algorithm/container.h"

std::string initializeSeedValue(const std::string& variable,
                                const std::string& type_of_variable,
                                const std::string& mode,
                                const std::string& output_type)
{
    // Define a set of allowed variable types
    const std::vector<std::string> allowed_types = {"int", "double", "float"};

    // Check if the type_of_variable is in the allowed types
    if (std::find(allowed_types.begin(), allowed_types.end(), type_of_variable) == allowed_types.end()) {
        // If not, construct a detailed error message
        std::string allowed_types_message = absl::StrJoin(allowed_types, ", ");
        throw std::invalid_argument("Unsupported variable type for seeding. Allowed types are: " + allowed_types_message);
    }

    // Add appropriate suffix based on the mode
    std::string suffix;
    if (mode == "tangent") {
        suffix = "_t";
    } else if (mode == "adjoint") {
        suffix = "_a";
    } else {
        throw std::invalid_argument("Unsupported mode. Supported modes are 'tangent' and 'adjoint'.");
    }

    // Add appropriate value 0 or 0.0
    std::string value;
    if (variable == "int") {
        value = "0";
    } else {
        value = "0.0";
    }

    // Construct the seed value assignment string
    std::string initSeed;
    if (output_type == "vector") {
        initSeed = absl::StrCat("std::vector<", type_of_variable, "> ", variable, suffix, "(", variable, ".size(),",value, ")");
    } else if (output_type == "scalar") {
        initSeed = absl::StrCat(type_of_variable, " ", variable, suffix, "(", value, ")");
    } else {
        throw std::invalid_argument("Unsupported output type. Supported types are 'vector' and 'scalar'.");
    }

    return initSeed;
}

// Function to set the seed value for a variable
std::string setSeedValue(const std::string& variable,
                         const std::string& mood,
                         const std::string& output_type,
                         const std::string& value_for_seeding,
                         const std::string& loop_level)
{
    // Add appropriate suffix based on the mood
    std::string suffix;
    if (mood == "tangent") {
        suffix = "_t";
    } else if (mood == "adjoint") {
        suffix = "_a";
    } else {
        throw std::invalid_argument("Unsupported mood. Supported moods are 'tangent' and 'adjoint'.");
    }

    // Construct the seed value assignment string
    std::string setSeed;
    if (output_type == "scalar") {
        setSeed = absl::StrCat(variable, suffix, " = ", value_for_seeding);
    } else if (output_type == "vector") {
        int num_loops = std::stoi(loop_level);
        if (num_loops < 0) {
            throw std::invalid_argument("Loop level must be a non-negative integer.");
        }

        std::string loop_index = std::string(num_loops, 'i');
        setSeed = absl::StrCat(variable, suffix,"[" , loop_index, "]", " = ", value_for_seeding);
    } else {
        throw std::invalid_argument("Unsupported output type. Supported types are 'scalar' and 'vector'.");
    }

    return setSeed;
}

// Function to set the seed value for a variable
std::string resetSeedValue(const std::string& variable,
                         const std::string& mood,
                         const std::string& output_type,
                         const std::string& loop_level)
{
    // Add appropriate suffix based on the mood
    std::string reset_Value = "0.0";
    std::string suffix;
    if (mood == "tangent") {
        suffix = "_t";
    } else if (mood == "adjoint") {
        suffix = "_a";
    } else {
        throw std::invalid_argument("Unsupported mood. Supported moods are 'tangent' and 'adjoint'.");
    }

    // Construct the seed value assignment string
    std::string resetSeed;
    if (output_type == "scalar") {
        resetSeed = absl::StrCat(variable, suffix, " = ", reset_Value);
    } else if (output_type == "vector") {
        int num_loops = std::stoi(loop_level);
        if (num_loops < 0) {
            throw std::invalid_argument("Loop level must be a non-negative integer.");
        }

        std::string loop_index = std::string(num_loops, 'i');
        resetSeed = absl::StrCat(variable, suffix,"[" , loop_index, "]", " = ", reset_Value);
    } else {
        throw std::invalid_argument("Unsupported output type. Supported types are 'scalar' and 'vector'.");
    }

    return resetSeed;
}


std::string setSeedValue_old(const std::string& variable, const std::string& type_of_variable, const std::string& value_for_seeding)
{
    // Define a set of allowed variable types
    const std::vector<std::string> allowed_types = {"int", "double", "float"};

    // Check if the type_of_variable is in the allowed types
    if (std::find(allowed_types.begin(), allowed_types.end(), type_of_variable) == allowed_types.end()) {
        // If not, construct a detailed error message
        std::string allowed_types_message = absl::StrJoin(allowed_types, ", ");
        throw std::invalid_argument("Unsupported variable type for seeding. Allowed types are: " + allowed_types_message);
    }

    // Split the comma-separated variable names
    std::vector<std::string> variables;
    std::istringstream variableStream(variable);
    std::string individualVariable;
    while (std::getline(variableStream, individualVariable, ',')) {
        // Trim leading and trailing whitespaces from individual variable names
        individualVariable = absl::StripAsciiWhitespace(individualVariable);
        variables.push_back(individualVariable);
    }

    // Construct the seed value assignment string for each variable
    std::vector<std::string> seed_assignments;
    for (const auto& var : variables) {
        std::string seed_assignment = absl::StrCat(type_of_variable, " ", var, " = ", value_for_seeding);
        seed_assignments.push_back(seed_assignment);
    }

    // Join the seed assignments into a single string with newline separators
    std::string result = absl::StrJoin(seed_assignments, "\n");

    return result;
}

/**
 * Retrieves the type of a variable from the given function call signature.
 *
 * @param callSignature the function call signature
 * @param variableName the name of the variable
 *
 * @return the type of the variable
 */
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

std::string getFunctionDriverCallSignature(const std::string &callSignature, const std::string &driver_type){
    std::vector<std::string> splittedCallSignature = absl::StrSplit(callSignature, absl::ByAnyChar(" ,()"),  absl::SkipEmpty());
    std::vector<std::string> driverType = absl::StrSplit(driver_type, absl::ByAnyChar(" ,()"),  absl::SkipEmpty());
    std::string driverCallSignature = absl::StrCat(splittedCallSignature[0]," ", splittedCallSignature[1], "_", driverType[0]);  
    return driverCallSignature;
}