#include <memory>
#include "../../src/SimpleConfigFile.hpp"

int main(int argc, char **argv) {
    // read into to config file
    auto configFile = std::make_unique<SimpleConfigFile>();
    configFile->readYamlFile(argv[1]);
}
