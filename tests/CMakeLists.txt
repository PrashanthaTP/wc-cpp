#Ref: http://google.github.io/googletest/quickstart-cmake.html

enable_testing()

add_executable(
  ccwc_test
  test.cpp
)

# target_include_directories(
#   ccwc_test
#   PRIVATE
#   ${CMAKE_SOURCE_DIR}/include
# )

target_link_libraries(
  ccwc_test
  ${PRJ_LIB_NAME}
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(ccwc_test)
