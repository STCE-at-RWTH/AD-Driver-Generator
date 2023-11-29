#include <string>
#include <stdexcept>

#include "utilities.hpp"

#include <sstream>
#include <vector>

std::string setSeedValue(std::string variable, std::string type_of_variable, std::string value_for_seeding)
{
    throw std::runtime_error("Not implemented yet");
}


std::vector<std::string> splitString(std::string inputString, char delimiter)
{
    // create output vector
  std::vector<std::string> splittedString;

  std::string word;
  std::stringstream stringStreamOfInputString(inputString);

  while (getline(stringStreamOfInputString, word, delimiter))
    splittedString.push_back(word);

  return splittedString;
}


std::string getTypeOfVariable(std::string callSignature, std::string variableName)
{
    auto callSignatureSplitted = splitString(callSignature, ' ');

    // search for variable name in callsignaturesplitted
    for (auto i = 0; i < callSignatureSplitted.size(); i++)
    {
        if (callSignatureSplitted[i] == variableName)
        {
            return callSignatureSplitted[i-1];
        }
    }
}
