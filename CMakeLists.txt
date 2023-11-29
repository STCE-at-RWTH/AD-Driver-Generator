cmake_minimum_required(VERSION 3.16)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

PROJECT(sisc-lab
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

ADD_SUBDIRECTORY(src)

FetchContent_Declare(
  googletest
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
  abseil
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG 8028a87c96df0fff5ab58daeec30c43ce6fb0d20 # 2023-11-28
)
set(ABSL_PROPAGATE_CXX_STD ON)

FetchContent_MakeAvailable(googletest abseil)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE libutilities)
