# General
The project uses [CMake](https://cmake.org/) as a build system.
For the unit tests [Google Test - GTest](https://google.github.io/googletest/) is used.

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
cmake --build build
```
and the project should be ready.

# Testing
In order to start the test suite run
```sh
cd build/src
ctest
```
and you should receive an overview about the tests and if they failed or not.
When your cmake version is recent enough `cmake --version` should be higher than `3.20` one might directly use
```sh
ctest --test-dir build/src
```

# Folder structure
Most of our code files will be in `src` where it might be good practice to follow [canonical project structure](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html).
```sh
.
├── CMakeLists.txt
├── README.md
└── src
    ├── CMakeLists.txt
    ├── main.cpp
    ├── utilities.cpp
    ├── utilities.hpp
    └── utilities.test.cpp

```
In this simple example the `utilities.cpp` file will include the functions and methods, whereas the `utilities.test.cpp` file will contain corresponding unit test for latter ones.
