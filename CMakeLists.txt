cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(sisc-lab
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG b75ecf1bed2fcd416b66c86cb6fe79122abf132e # 2024-02-08
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
        abseil
        GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
        GIT_TAG 563c86a80c06ffbbfaa2ea792a9c255a5c258cf0 # 2024-02-07
)
set(ABSL_PROPAGATE_CXX_STD ON)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG 4afd53b0d3140ba2eb85816bfced209cf37ff096 # 2024-01-26
)

FetchContent_MakeAvailable(googletest abseil yaml-cpp)

enable_testing()
add_subdirectory(src)
add_subdirectory(tests)
