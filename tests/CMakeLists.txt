cmake_minimum_required(VERSION 3.24)
project(txt2tok-tests LANGUAGES CXX)

include(GoogleTest)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(googletest)

add_executable(txt2tok-tests
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tests.cpp
)

target_link_libraries(txt2tok-tests PRIVATE
    GTest::gtest_main
    txt2tok
)

enable_testing()
gtest_discover_tests(txt2tok-tests)
