cmake_minimum_required(VERSION 3.24)
project(txt2tok LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Sanitizer is enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g -fsanitize=leak")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -O3")
endif()

add_subdirectory(tests)
add_subdirectory(txt2tok)
