#ifndef SISC_LAB_DRIVERFACTORY_HPP
#define SISC_LAB_DRIVERFACTORY_HPP

#include <iostream>
#include <string>
#include <memory>

#include "Driver.hpp"
#include "GradientDriver.hpp"
#include "JacobianDriver.hpp"

class DriverFactory {
public:
    std::unique_ptr<Driver> getDriverType(const ConfigFile *configFile);
};

std::unique_ptr<Driver> DriverFactory::getDriverType(const ConfigFile *configFile) {
    if (configFile->getDriverType() == "gradient") {
        return std::make_unique<GradientDriver>();
    } 
    else if (configFile->getDriverType() == "jacobian") {
        return std::make_unique<JacobianDriver>();
    }
    else {
        // stop
        std::cout << "Invalid driver type: " << configFile->getDriverType() << std::endl;
        std::exit(1);
    }
}

#endif //SISC_LAB_DRIVERFACTORY_HPP
