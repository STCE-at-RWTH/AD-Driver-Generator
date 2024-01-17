//
// Created by felix on 1/17/24.
//

#ifndef SISC_LAB_GRADIENTDRIVER_HPP
#define SISC_LAB_GRADIENTDRIVER_HPP

#include "Driver.hpp"
#include "Utilities.hpp"

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

    strings.push_back(utilities->createLoopSignature(configFile->getActiveVariables(), level));
    counter.push_back(level);
    level++;

    strings.push_back(utilities->setSeedValue(configFile->getActiveVariables(), "1.0", std::to_string(level-1)));
    counter.push_back(level);

    strings.push_back(utilities->getAssociationByNameSignature());
    counter.push_back(level);

    strings.push_back(utilities->resetSeedValue(configFile->getActiveVariables(), std::to_string(level-1)));
    counter.push_back(level);

    return std::make_pair(strings, counter);
}



#endif //SISC_LAB_GRADIENTDRIVER_HPP
