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

add_test(NAME JacobianDriver.ExternalYAMLFile_TangentMode1ActiveVector1OutputVector
        COMMAND driver
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp_jacobian_tangent_1_act_vec_1_out_vector.yml"
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp_jacobian_tangent_1_act_vec_1_out_vector.txt"
)

add_test(NAME JacobianDriver.ExternalYAMLFile_AjointMode1ActiveVector1OutputVector
        COMMAND driver
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp_jacobian_adjoint_1_act_vec_1_out_vector.yml"
        "${CMAKE_CURRENT_SOURCE_DIR}/cpp_jacobian_adjoint_1_act_vec_1_out_vector.txt"
)