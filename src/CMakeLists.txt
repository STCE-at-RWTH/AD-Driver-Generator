enable_testing()

add_library(libutilities
  utilities.cpp
  utilities.hpp
)

target_link_libraries(libutilities
  absl::strings
)
target_link_libraries(libutilities
  absl::algorithm
)


add_executable(utilities.test
  utilities.test.cpp
)

target_link_libraries(utilities.test
  libutilities
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utilities.test)
