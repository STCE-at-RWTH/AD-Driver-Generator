enable_testing()
include(GoogleTest)

add_library(libutilities
        utilities.cpp
        utilities.hpp
        ConfigFile.hpp
        SimpleConfigFile.hpp
)

target_link_libraries(libutilities
        absl::strings
        absl::algorithm
        yaml-cpp::yaml-cpp
)

add_executable(utilities.test
  utilities.test.cpp
)

target_link_libraries(utilities.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(utilities.test)

add_executable(SimpleConfigFile.test
        SimpleConfigFile.test.cpp)

target_link_libraries(SimpleConfigFile.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(SimpleConfigFile.test)

