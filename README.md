# General
The project uses [CMake](https://cmake.org/) as a build system.
For the unit tests [Google Test - GTest](https://google.github.io/googletest/) is used.

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
ctest --test-dir build/src/
```
and you should receive an overview about the tests and if they failed or not.

# Folder structure
Most of our code files will be in `src` where it might be good practice to follow [canonical project structure](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1204r0.html).
```sh
.
├── CMakeLists.txt
├── README.md
└── src
    ├── CMakeLists.txt
    ├── run_try.cpp
    ├── try.hpp
    └── try.test.cpp
```
In this simple example the `try.hpp` file will include the functions and methods, whereas the `try.test.cpp` file will contain corresponding unit test for latter ones.
Finally in `run_try.cpp` in this example would then be the executable which works on the methods.
