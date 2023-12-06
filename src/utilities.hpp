#include <vector>
#include <string>

#ifndef SISC_LAB_UTILITIES_HPP
#define SISC_LAB_UTILITIES_HPP

std::string setSeedValue(std::string variable, std::string type_of_variable, std::string value_for_seeding);

std::string getTypeOfVariable(const std::string &callSignature, const std::string &variableName);

std::string getAssociationByNameSignature(std::string call_signature, std::string active_variable);

#endif //SISC_LAB_UTILITIES_HPP
