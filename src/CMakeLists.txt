include(GoogleTest)

add_library(libutilities
        Utilities.hpp
        UtilitiesMock.hpp
        CppUtilities.hpp
        ConfigFile.hpp
        ConfigFileMock.hpp
        SimpleConfigFile.hpp
        OutputParser.hpp
        CppOutputParser.hpp
        Driver.hpp
        GradientDriver.hpp
        JacobianDriver.hpp
        DriverFactory.hpp
        UtilitiesFactory.hpp
)

target_link_libraries(libutilities
        absl::strings
        absl::algorithm
        yaml-cpp::yaml-cpp
        GTest::gmock
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

add_executable(JacobianDriver.test
        JacobianDriver.test.cpp)

target_link_libraries(JacobianDriver.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(JacobianDriver.test)

add_executable(DriverFactory.test
        DriverFactory.test.cpp)

target_link_libraries(DriverFactory.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(DriverFactory.test)

add_executable(UtilitiesFactory.test
        UtilitiesFactory.test.cpp)
target_link_libraries(UtilitiesFactory.test
        libutilities
        GTest::gtest_main
)
gtest_discover_tests(UtilitiesFactory.test)
