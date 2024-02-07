include(GoogleTest)

add_library(libutilities
        Utilities.hpp
        CppUtilities.hpp
        ConfigFile.hpp
        SimpleConfigFile.hpp
        OutputParser.hpp
        CppOutputParser.hpp
        Driver.hpp
        GradientDriver.hpp
        DriverFactory.hpp
        UtilitiesFactory.hpp
)

target_link_libraries(libutilities
        absl::strings
        absl::algorithm
        yaml-cpp::yaml-cpp
)

add_executable(SimpleConfigFile.test
        SimpleConfigFile.test.cpp)

target_link_libraries(SimpleConfigFile.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(SimpleConfigFile.test)

add_executable(CppOutputParser.test
        CppOutputParser.test.cpp
)

target_link_libraries(CppOutputParser.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(CppOutputParser.test)

add_executable(CppUtilities.test
        CppUtilities.test.cpp
)

target_link_libraries(CppUtilities.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(CppUtilities.test)

add_executable(GradientDriver.test
        GradientDriver.test.cpp)

target_link_libraries(GradientDriver.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(GradientDriver.test)
