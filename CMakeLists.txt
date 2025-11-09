cmake_minimum_required(VERSION 4.0.2)
project(
    Clad
    VERSION 0.0.1
    DESCRIPTION "A game engine"
    LANGUAGES CXX
)

option(BUILD_DOCS "Whether to build the documentation" OFF)
option(BUILD_EXAMPLES "Whether to build the examples" OFF)
option(BUILD_TESTS "Whether to build the tests" OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

add_subdirectory(thirdparty)

set(LIBRARY_NAME clad)
add_library(${LIBRARY_NAME} STATIC
    src/clad/app/schedule.cpp
    src/clad/input/input.cpp
)
target_include_directories(${LIBRARY_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
target_link_libraries(${LIBRARY_NAME} PRIVATE SDL3::SDL3)

if(BUILD_DOCS)
    add_subdirectory(docs)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
