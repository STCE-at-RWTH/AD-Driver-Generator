#ifndef SISC_LAB_UTILITIESFACTORY_HPP
#define SISC_LAB_UTILITIESFACTORY_HPP

#include <memory>
#include "Utilities.hpp"
#include "CppUtilities.hpp"

class UtilitiesFactory {
public:
    std::unique_ptr<Utilities> getUtilities(const ConfigFile *configFile);
};

std::unique_ptr<Utilities> UtilitiesFactory::getUtilities(const ConfigFile *configFile) {
    if (configFile->getLanguage() == "cpp") {
        std::vector<CallSignature> callSignatures = configFile->getFunctions();
        return std::unique_ptr<CppUtilities>(new CppUtilities(callSignatures[0]));
    } else {
        // abort
        std::abort();
    }
}

#endif //SISC_LAB_UTILITIESFACTORY_HPP
