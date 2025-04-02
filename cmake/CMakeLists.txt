cmake_minimum_required(VERSION 3.14)
project(dit639_group14)

# Set C++ standard
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)

# Define source and include directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# Include directories
include_directories(${INCLUDE_DIR})

# Add source files
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

# Define the executable
add_executable(dit639_group14 ${SOURCES})

# Enable testing
#include(CTest)
#enable_testing()


# Add tests if test files exist
#file(GLOB TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
#if(TEST_SOURCES)
#    add_executable(run_tests ${TEST_SOURCES})
#    target_include_directories(run_tests PRIVATE ${INCLUDE_DIR})
#    add_test(NAME RunTests COMMAND run_tests)
#endif()


# Install target
install(TARGETS cps_project DESTINATION bin)
