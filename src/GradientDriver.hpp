#ifndef SISC_LAB_GRADIENTDRIVER_HPP
#define SISC_LAB_GRADIENTDRIVER_HPP

#include "Driver.hpp"
#include "Utilities.hpp"
#include "absl/strings/match.h"

class GradientDriver : public Driver {
public:

    std::pair<std::vector<std::string>, std::vector<int>>
    createDriver(Utilities *utilities, ConfigFile *configFiles) override;

};;

std::pair<std::vector<std::string>, std::vector<int>> GradientDriver::createDriver(Utilities *utilities, ConfigFile *configFile) {
    std::vector<std::string> strings;
    std::vector<int> counter;
    int level {0};

    strings.push_back(utilities->createDriverCallSignature());
    counter.push_back(level);

    level++;

    strings.push_back(utilities->initializeSeedValue(configFile->getActiveVariables()));
    counter.push_back(level);
    strings.push_back(utilities->initializeSeedValue(configFile->getOutputVariables()));
    counter.push_back(level);

    if ( absl::StrContains(strings.back(), "std::vector")){
        // if ( configFile->getMode() == "adjoint"){
            strings.push_back(utilities->createLoopSignature(configFile->getOutputVariables(), level));
            counter.push_back(level);
            level++;
        // }
    } else if ( absl::StrContains(strings[strings.size() - 2], "std::vector") ){
        // if ( configFile->getMode() == "tangent"){
            strings.push_back(utilities->createLoopSignature(configFile->getActiveVariables(), level));
            counter.push_back(level);
            level++;
        // }
    }

    if ( configFile->getMode() == "tangent") {
        strings.push_back(utilities->setSeedValue(configFile->getActiveVariables(), "1.0", std::to_string(level-1)));
        counter.push_back(level);

    } else if (configFile->getMode() == "adjoint"){
        strings.push_back(utilities->setSeedValue(configFile->getOutputVariables(), "1.0", std::to_string(level-1)));
        counter.push_back(level);
    } else {
        throw std::invalid_argument("Unsupported mode: '" + configFile->getMode() + "'. Supported modes are 'tangent' and 'adjoint'.");
    }

    strings.push_back(utilities->getAssociationByNameSignature());
    counter.push_back(level);

//    strings.push_back(utilities->harvest(configFile->getActiveVariables(), std::to_string(level-1)));
//     counter.push_back(level);


    if ( configFile->getMode() == "tangent") {
        strings.push_back(utilities->harvest(configFile->getOutputVariables(), std::to_string(level-1)));
        counter.push_back(level);
    } else if (configFile->getMode() == "adjoint"){
        strings.push_back(utilities->harvest(configFile->getActiveVariables(), std::to_string(level-1)));
        counter.push_back(level);
    } else {
        throw std::invalid_argument("Unsupported mode: '" + configFile->getMode() + "'. Supported modes are 'tangent' and 'adjoint'.");
    }

    if ( configFile->getMode() == "tangent") {
        strings.push_back(utilities->resetSeedValue(configFile->getActiveVariables(), std::to_string(level-1)));
        counter.push_back(level);
    } else if (configFile->getMode() == "adjoint"){
        strings.push_back(utilities->resetSeedValue(configFile->getOutputVariables(), std::to_string(level-1)));
        counter.push_back(level);
    } else {
        throw std::invalid_argument("Unsupported mode: '" + configFile->getMode() + "'. Supported modes are 'tangent' and 'adjoint'.");
    }

    return std::make_pair(strings, counter);
}



#endif //SISC_LAB_GRADIENTDRIVER_HPP
