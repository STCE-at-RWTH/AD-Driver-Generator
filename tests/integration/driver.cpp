#include <memory>
#include <fstream>
#include "../../src/SimpleConfigFile.hpp"
#include "../../src/DriverFactory.hpp"
#include "../../src/UtilitiesFactory.hpp"
#include "../../src/CppOutputParser.hpp"

int main(int argc, char **argv) {
    const std::string FILENAME{argv[1]};
    const std::string FILENAME_OUTPUT{argv[2]};

    // read into to config file
    auto configFile = std::make_unique<SimpleConfigFile>();
    configFile->readYamlFile(FILENAME);

    // create utilities for config file
    auto utilities = std::make_unique<UtilitiesFactory>()->getUtilities(configFile.get());
    auto parser = std::make_unique<CppOutputParser>();

    // create driver
    auto driver = std::make_unique<DriverFactory>()->getDriverType(configFile.get());
    auto output_pair = driver->createDriver(utilities.get(), configFile.get());

    parser->parse(output_pair);

    std::ofstream OutputFile (FILENAME_OUTPUT);
    for (auto const &str: output_pair.first) {
        OutputFile << str << std::endl;
    }

    OutputFile.close();
}