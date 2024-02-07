#ifndef SISC_LAB_DRIVERFACTORY_HPP
#define SISC_LAB_DRIVERFACTORY_HPP

#include <string>
#include <memory>
#include "Driver.hpp"
#include "GradientDriver.hpp"

class DriverFactory {
public:
    std::unique_ptr<Driver> getDriverType(const ConfigFile *configFile);
};

std::unique_ptr<Driver> DriverFactory::getDriverType(const ConfigFile *configFile) {
    if (configFile->getDriverType() == "gradient") {
        return std::make_unique<GradientDriver>();
    } else {
        // abort
        std::abort();
    }
}

#endif //SISC_LAB_DRIVERFACTORY_HPP
