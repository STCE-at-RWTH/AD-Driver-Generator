cmake_minimum_required(VERSION 3.16)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

PROJECT(sisc-lab CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)

ADD_SUBDIRECTORY(src)

FetchContent_Declare(
  googletest
  # currently v1.14
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
  )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(run_try src/run_try.cpp)
