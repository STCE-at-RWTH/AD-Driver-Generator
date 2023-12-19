enable_testing()

add_library(libutilities
        utilities.cpp
        utilities.hpp
        ConfigFile.hpp
        SimpleConfigFile.hpp
)

target_link_libraries(libutilities
        absl::strings
        absl::algorithm
)


add_executable(utilities.test
        utilities.test.cpp
)

target_link_libraries(utilities.test
        libutilities
        GTest::gtest_main
)

add_executable(ConfigFile.test
        SimpleConfigFile.test.cpp)

target_link_libraries(ConfigFile.test
        libutilities
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utilities.test)
