#include <vector>
#include <string>

#ifndef SISC_LAB_UTILITIES_HPP
#define SISC_LAB_UTILITIES_HPP

std::string setSeedValue(std::string variable, std::string type_of_variable, std::string value_for_seeding);

std::string getTypeOfVariable(std::string callSignature, std::string variableName);

std::vector<std::string> splitString(std::string inputString, char delimiter);

#endif //SISC_LAB_UTILITIES_HPP
