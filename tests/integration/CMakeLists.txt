add_executable(driver driver.cpp)
target_link_libraries(driver PRIVATE libutilities)

add_test(NAME GradientDriver.ExternalYAMLFile_WhenSingleActiveVariable
        COMMAND driver
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp_gradient_single_active_variable.yml"
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp_gradient_single_active_variable.txt"
)

add_test(NAME GradientDriver.ExternalYAMLFile_WhenTwoActiveVariables
        COMMAND driver
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp_gradient_two_active_variable.yml"
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp_gradient_two_active_variable.txt"
)