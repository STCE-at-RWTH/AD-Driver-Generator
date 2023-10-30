cmake_minimum_required(VERSION 3.20)

PROJECT(SiSc CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)

ADD_SUBDIRECTORY(src)
# ADD_EXECUTABLE(try src/try.cpp)

cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(
  googletest
  # currently v1.14
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
  )

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
