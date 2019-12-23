cmake_minimum_required(VERSION 3.10)

project(DijkstraSkew VERSION 1.0)

# target_include_directories(DijkstraSkew PUBLIC src/)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(External_GTest.cmake)

add_executable(alltest test/AllTests.cpp)
target_include_directories(alltest PUBLIC src/)

target_link_libraries(alltest ${GTEST_LIBRARY})

enable_testing()
include(GoogleTest)
gtest_add_tests(
    TARGET alltest
    TEST_LIST test_targets
)

set_tests_properties(${test_targets} PROPERTIES TIMEOUT 10)
