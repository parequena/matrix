cmake_minimum_required(VERSION 3.0.0)
project(matrix VERSION 0.1.0)

set(ALL_CLANG_WARNINGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough")
set(ALL_GCC_WARNINGS "${ALL_CLANG_WARNINGS} -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wuseless-cast")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ALL_CLANG_WARNINGS} -Werror")
else()
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${ALL_GCC_WARNINGS} -Werror")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(matrix INTERFACE)
target_include_directories(matrix INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

####################################################################
## Unit Test with Gtest
####################################################################
file(GLOB_RECURSE GTEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
find_package(GTest REQUIRED)
enable_testing()
add_executable(unit-test ${GTEST_SRC_FILES})
target_link_libraries(unit-test gtest gtest_main)
add_test(UnitTest unit-test)