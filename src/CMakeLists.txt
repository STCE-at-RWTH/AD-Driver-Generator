enable_testing()

add_executable(
  try_test
  try.test.cpp
  )
target_link_libraries(
  try_test
  GTest::gtest_main
  )

include(GoogleTest)
gtest_discover_tests(try_test)
