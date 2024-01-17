#ifndef SISC_LAB_UTILITIES_HPP
#define SISC_LAB_UTILITIES_HPP

#include <vector>
#include <string>
#include "ConfigFile.hpp"

class Utilities{
public:
    Utilities() = default;
    virtual ~Utilities() = default;

    virtual std::string getTypeOfVariable(const std::string &activeVariable) = 0;
    virtual std::string getAssociationByNameSignature() = 0;
    virtual std::string createLoopSignature(const std::string &activeVariable, int level) = 0;
    virtual std::string setSeedValue(const std::string &variable, const std::string &value_for_seeding, const std::string &loop_level) = 0;
    virtual std::string initializeSeedValue(const std::string &variable) = 0;
    virtual std::string resetSeedValue(const std::string &variable, const std::string &loop_level) = 0;
    virtual std::string harvest(const std::string &variable, const std::string &loop_level) = 0;
    virtual std::string createDriverCallSignature() = 0;
    virtual std::string createDriverCallArguments() = 0;

};

// std::string initializeSeedValue(const std::string& variable,
//                                 const std::string& type_of_variable,
//                                 const std::string& mode);
// std::string setSeedValue(const std::string& variable,
//                          const std::string& type_of_variable,
//                          const std::string& mood,
//                          const std::string& value_for_seeding,
//                          const std::string& loop_level);
// std::string resetSeedValue(const std::string& variable,
//                            const std::string& type_of_variable,
//                            const std::string& mood,
//                            const std::string& loop_level);
//
// std::string setSeedValue_old(const std::string& variable, const std::string& type_of_variable, const std::string& value_for_seeding);
//
//
// std::string createDriverCallSignature(const std::string &callSignature, const std::string &driver_type);

#endif //SISC_LAB_UTILITIES_HPP
