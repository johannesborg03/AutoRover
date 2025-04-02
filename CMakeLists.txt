cmake_minimum_required(VERSION 3.14)
project(dit639_group14)


set(CMAKE_CXX_STANDARD 11)

# Find all .cpp files in src/ dynamically
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})
