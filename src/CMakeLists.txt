enable_testing()

add_library(Utilities utilities.cpp utilities.hpp)

add_executable(
        utilities.test
        utilities.test.cpp
)
target_link_libraries(
        utilities.test
        Utilities
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utilities.test)
