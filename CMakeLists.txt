cmake_minimum_required(VERSION 3.0.0)
project(matrix VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Set warnings from CMakePressets.json
set(PROJECT_WARNINGS "${GENERAL_COMPILER_WARNINGS};${SPECIFIC_COMPILER_WARNINGS}")

add_library(matrix INTERFACE)
target_include_directories(matrix INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add DEBUG_BUILD macro and Sanitizers.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(matrix INTERFACE DEBUG_BUILD)
    target_compile_options(matrix INTERFACE -fsanitize=address,undefined)
    target_link_libraries(matrix INTERFACE -fsanitize=address,undefined)
endif()

####################################################################
## Unit Test with Gtest
####################################################################
file(GLOB_RECURSE GTEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
find_package(GTest REQUIRED)
enable_testing()
add_executable(unit-test ${GTEST_SRC_FILES})
add_test(UnitTest unit-test)

# Add DEBUG_BUILD macro and Sanitizers.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(unit-test PRIVATE DEBUG_BUILD)
    target_compile_options(unit-test PRIVATE -fsanitize=address,undefined)
    target_link_libraries(unit-test PRIVATE tbb gtest gtest_main -fsanitize=address,undefined)
else()
target_link_libraries(unit-test tbb gtest gtest_main)
endif()

####################################################################
## Main
####################################################################
add_executable(main main.cpp)

# Add DEBUG_BUILD macro and Sanitizers.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(main PRIVATE DEBUG_BUILD)
    target_compile_options(main PRIVATE -fsanitize=address,undefined)
    target_link_libraries(main PRIVATE tbb -fsanitize=address,undefined)
    else()
    target_link_libraries(main tbb)
endif()