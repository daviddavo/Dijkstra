cmake_minimum_required(VERSION 3.10)

project(DijkstraSkew VERSION 1.0)

# target_include_directories(DijkstraSkew PUBLIC src/)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(External_GTest.cmake)

add_library(skewheap INTERFACE)
target_sources(skewheap INTERFACE "${PROJECT_SOURCE_DIR}/src/skewheap.h")
# target_include_directories(skewheap INTERFACE src/)

add_library(graph INTERFACE)
target_sources(graph INTERFACE "${PROJECT_SOURCE_DIR}/src/graph.h")

add_library(dijkstra INTERFACE)
target_sources(dijkstra INTERFACE "${PROJECT_SOURCE_DIR}/src/dijkstra.h")
target_link_libraries(dijkstra INTERFACE skewheap graph)
# target_include_directories(dijkstra PUBLIC src)

add_library(graphReader INTERFACE)
target_sources(graphReader INTERFACE "${PROJECT_SOURCE_DIR}/src/graphReader.h" "${PROJECT_SOURCE_DIR}/src/graphReader.cpp")
target_link_libraries(graphReader INTERFACE graph)

add_executable(testSkewHeap test/testSkewHeap.cpp)
add_executable(testDijkstra test/testDijkstra.cpp)
add_executable(testReader test/testReader.cpp)

target_link_libraries(testSkewHeap ${GTEST_LIBRARY} skewheap)
target_include_directories(testSkewHeap PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(testDijkstra ${GTEST_LIBRARY} dijkstra)
target_include_directories(testDijkstra PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(testReader ${GTEST_LIBRARY} graphReader graph)
target_include_directories(testReader PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

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

gtest_add_tests(
    TARGET testReader
    TEST_LIST test_targets
)

set_tests_properties(${test_targets} PROPERTIES TIMEOUT 10)
