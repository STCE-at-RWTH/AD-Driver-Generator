#ifndef SISC_LAB_UTILITIESFACTORY_HPP
#define SISC_LAB_UTILITIESFACTORY_HPP

#include <memory>
#include <iostream>

#include "Utilities.hpp"
#include "CppUtilities.hpp"

class UtilitiesFactory {
public:
    static std::unique_ptr<Utilities> getUtilities(const ConfigFile *configFile);
};

std::unique_ptr<Utilities> UtilitiesFactory::getUtilities(const ConfigFile *configFile) {
    if (configFile->getLanguage() == "cpp") {
        std::vector<CallSignature> callSignatures = configFile->getFunctions();
        return std::make_unique<CppUtilities>(callSignatures[0]);
    } else {
        // end program with exit code 1
        std::cout << "Invalid input language type: " << configFile->getLanguage() << std::endl;
        std::exit(1);
    }
}

#endif //SISC_LAB_UTILITIESFACTORY_HPP