add_executable(driver_yaml driver.cpp)
target_link_libraries(driver_yaml PRIVATE libutilities)

add_test(NAME SimpleConfigFile.ExternalYAMLFile_WhenSingleActiveVariable
        COMMAND driver_yaml
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp_single_active_variable.yml")
