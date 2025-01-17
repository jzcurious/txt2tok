cmake_minimum_required(VERSION 3.24)
project(txt2tok-lib LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
  txt2lines
  GIT_REPOSITORY https://github.com/jzcurious/txt2lines.git
  GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(txt2lines)

FetchContent_Declare(
  string-span
  GIT_REPOSITORY https://github.com/jzcurious/string-span.git
  GIT_TAG v1.0.0
)
FetchContent_MakeAvailable(string-span)

file(GLOB_RECURSE SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_library(txt2tok STATIC ${SRC})

target_compile_definitions(txt2tok PRIVATE
    "DEBUG=$<CONFIG:Debug>"
)

target_include_directories(txt2tok PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(txt2tok PUBLIC
    txt2lines
    strspan
)
