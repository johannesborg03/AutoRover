cmake_minimum_required(VERSION 3.14)
project(dit639_group14)


set(CMAKE_CXX_STANDARD 11)

# Find all .cpp files in src/ dynamically
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

enable_testing()

#Add tests files downbelow
add_executable(
    ${PROJECT_NAME}-Runner 
"${CMAKE_CURRENT_SOURCE_DIR}/tests/TestPrimeChecker.cpp" 
"${CMAKE_CURRENT_SOURCE_DIR}/src/PrimeChecker.cpp"
)



add_test(NAME ${PROJECT_NAME}-Runner COMMAND ${PROJECT_NAME}-Runner)
