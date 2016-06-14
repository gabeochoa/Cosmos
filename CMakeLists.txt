cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(cosmos)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()


enable_language(C CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "-std=c++11 -Wall -Wextra -Wpedantic -Werror")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

endif()

include_directories(inc)
file(GLOB SOURCES "src/*.cpp")
add_executable(cosmos ${SOURCES})

set(GOOGLETEST_ROOT ext/gtest/googletest CACHE STRING "Google Test source root")
include_directories(
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include
    )

set(GOOGLETEST_SOURCES
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
    ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
    )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(googletest ${GOOGLETEST_SOURCES})

add_executable(
    unit_tests
    test/main.cpp
    test/test_parser.cpp
    )

add_dependencies(unit_tests googletest)

target_link_libraries(
    unit_tests
    googletest
    pthread
    )

include(CTest)
enable_testing()

add_test(unit ${PROJECT_BINARY_DIR}/unit_tests)