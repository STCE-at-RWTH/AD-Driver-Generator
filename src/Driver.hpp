#ifndef SISC_LAB_DRIVER_HPP
#define SISC_LAB_DRIVER_HPP

#include <utility>
#include <vector>
#include <string>

#include "Utilities.hpp"

class Driver {
public:
    Driver() = default;
    virtual ~Driver() = default;

    virtual std::pair<std::vector<std::string>, std::vector<int>>
    createDriver(Utilities *utilities, ConfigFile *configFiles) = 0;

};

#endif //SISC_LAB_DRIVER_HPP
