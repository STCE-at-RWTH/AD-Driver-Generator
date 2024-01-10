#ifndef SISC_LAB_OUTPUTPARSER_HPP
#define SISC_LAB_OUTPUTPARSER_HPP

#include <string>
#include <vector>

class OutputParser {
public:
    virtual ~OutputParser() = default;
    virtual void parse(std::pair<std::vector<std::string>, std::vector<int>> &input) = 0;
};

#endif //SISC_LAB_OUTPUTPARSER_HPP
