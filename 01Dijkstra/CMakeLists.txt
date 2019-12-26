cmake_minimum_required(VERSION 3.10)

project(DijkstraSkew VERSION 1.0)

# target_include_directories(DijkstraSkew PUBLIC src/)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(External_GTest.cmake)

find_package(Boost 1.69 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

file(GLOB SOURCES src/*.c src/*.h)
add_executable(testSkewHeap test/testSkewHeap.cpp) # ${SOURCES})
add_executable(testDijkstra test/testDijkstra.cpp ${SOURCES})
target_include_directories(testSkewHeap PUBLIC src/)
target_include_directories(testDijkstra PUBLIC src/)
add_library(dijkstra src/dijkstra.cpp src/dijkstra.h)

target_link_libraries(testSkewHeap ${GTEST_LIBRARY} )
target_link_libraries(testDijkstra ${GTEST_LIBRARY} ${Boost_LIBRARIES} dijkstra)

enable_testing()
include(GoogleTest)
gtest_add_tests(
    TARGET testSkewHeap
    TEST_LIST test_targets
)

gtest_add_tests(
    TARGET testDijkstra
    TEST_LIST test_targets
)

set_tests_properties(${test_targets} PROPERTIES TIMEOUT 10)
