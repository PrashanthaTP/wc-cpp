#Ref: http://google.github.io/googletest/quickstart-cmake.html

enable_testing()

add_executable(
  ccwc_test
  test.cpp
)
target_link_libraries(
  ccwc_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ccwc_test)
