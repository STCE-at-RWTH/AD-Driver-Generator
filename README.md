# General
The project uses [CMake](https://cmake.org/) as a build system.
For the unit tests [Google Test - GTest](https://google.github.io/googletest/) is used.
For the invocation of the unit tests as well as integration tests [CTest](https://cmake.org/cmake/help/latest/manual/ctest.1.html) is used.

# Building on the Cluster
Load the appropriate modules such as
```sh
ml GCC CMake
```
or
```sh
ml Clang CMake
```
and then you can build.

# Building
Run in the main directory
```sh
cmake -S . -B build
cmake --build build -j 4
```
and the project should be ready for subsequent builds the last line is sufficient.
If one wants to build another configuration  the first line can be appended with `-DCMAKE_BUILD_TYPE=Debug` or `-DCMAKE_BUILD_TYPE=Release`.

# Testing
When your cmake version is recent enough `cmake --version` should be higher than `3.20` one might directly use
```sh
ctest --test-dir build
```
With this invocation both unit tests which are in `build/src` as well as integration tests which are in `build/test` are executed.
If the cmake version is lower than `3.20` one might use
```sh
cd build
ctest
```
and you should receive an overview about the tests and if they failed or not.
As the project uses quite common setup for this also your preferred IDE should be able to run the tests over some plugins.

# Folder structure
Most of our code files will be in `src` where it might be good practice to follow [canonical project structure](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html).
```sh
.
├── CMakeLists.txt
├── README.md
├── src
    ├── CMakeLists.txt
    ├── Utilities.hpp
    ├── UtilitiesMock.hpp
    ├── CppUtilities.hpp
    └── CppUtilities.test.cpp
    ...
└── tests
```
In this simple example the `Utilities.hpp` file will include the abstract class interface, whereas the `CppUtilities.cpp` file will contain a specific implementation for the C++ language.
When another class wants to use the `Utilities`, one can use the mock implementation in `UtilitiesMock.hpp` to have them decoupled.
Therefore also corresponding unit tests for a specific implementation should be post-fixed with `.test.cpp`.

# Third party Dependencies
Currently following third party libraries are used to perform some tasks.
Both are pulled in automatically when running CMake.
- [Abseil](https://abseil.io/)
- [YAML-CPP](https://github.com/jbeder/yaml-cpp)

# Tutorials - Documentation
Following are some small tutorials as well as documentation to get started with the tools used in this project.

## [Git Tutorial](https://learngitbranching.js.org/) 
For local development interesting up to `Moving Work Around`.
For remote development one can recommend both sections.

## [Google Test/Mock](https://google.github.io/googletest/)
Recommendation is to read over the [GoogleTest Primer](https://google.github.io/googletest/primer.html) and then to look at the [Mocking for Dummies](https://google.github.io/googletest/gmock_for_dummies.html).
This should give sufficient background for understanding the tests and the structure in this repository.
When adding new files the [Quickstart: CMake](https://google.github.io/googletest/quickstart-cmake.html) provides guidance on how to discover the tests in the new files.