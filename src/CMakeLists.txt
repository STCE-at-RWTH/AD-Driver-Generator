enable_testing()
include(GoogleTest)

add_library(libutilities
        Utilities.cpp
        Utilities.hpp
        ConfigFile.hpp
        SimpleConfigFile.hpp
        OutputParser.hpp
        CppOutputParser.hpp
)

target_link_libraries(libutilities
        absl::strings
        absl::algorithm
        yaml-cpp::yaml-cpp
)

add_executable(Utilities.test
        Utilities.test.cpp
)

target_link_libraries(Utilities.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(Utilities.test)

add_executable(SimpleConfigFile.test
        SimpleConfigFile.test.cpp)

target_link_libraries(SimpleConfigFile.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(SimpleConfigFile.test)

add_executable(CppOutputParser.test
        CppOutputParser.test.cpp)

target_link_libraries(CppOutputParser.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(CppOutputParser.test)

