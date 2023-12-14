#include <vector>
#include <string>

#ifndef SISC_LAB_UTILITIES_HPP
#define SISC_LAB_UTILITIES_HPP

// std::string initializeSeedValue(const std::string& variable, const std::string& type_of_variable);

std::string setSeedValue(const std::string& variable, const std::string& type_of_variable, const std::string& value_for_seeding);

std::string getTypeOfVariable(const std::string &callSignature, const std::string &variableName);

std::string createLoopSignature(const std::string &activeVariable, int level);

std::string getAssociationByNameSignatureCompute(const std::string &callSignature, const std::string &activeVariable);

std::string createDriverCallSignature(const std::string &callSignature, const std::string &driver_type);

#endif //SISC_LAB_UTILITIES_HPP
