#ifndef SISC_LAB_CALLSIGNATURE_HPP
#define SISC_LAB_CALLSIGNATURE_HPP

#include <string>

class CallSignature{
public:
    std::string call_signature{};
    std::string active{};
    std::string output{};
    std::string mode{};
    std::string driver_type{};

    CallSignature( std::string_view _call_signature,
        std::string_view _active,
        std::string_view _output,
        std::string_view _mode,
        std::string_view _driver_type)
        : call_signature(_call_signature),
          active(_active),
          output(_output),
          mode(_mode),
          driver_type(_driver_type) {}
};

#endif //SISC_LAB_CALLSIGNATURE_HPP
