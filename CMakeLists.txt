cmake_minimum_required(VERSION 3.18)
project(OSM_Routing_Project)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.10.0.zip
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
    GIT_TAG        9.0.0
)
FetchContent_MakeAvailable(tinyxml2)

add_library(
    osm_routing
    src/build_graph.cpp
    src/a_star.cpp
    # Add other source files here
)

# Specify the include directory
target_include_directories(osm_routing PUBLIC include)
target_include_directories(osm_routing PRIVATE ${tinyxml2_SOURCE_DIR})


target_link_libraries(
    osm_routing
    tinyxml2
)

enable_testing()

add_executable(
  osm_routing_tests
  tests/osm_routing_test.cpp
  # Add other test files here
)

# Create an executable for AStar testing
add_executable(astar_test src/astar_main.cpp)

target_link_libraries(astar_test osm_routing)

target_link_libraries(
  osm_routing_tests
  gtest_main
  osm_routing
)

include(GoogleTest)
gtest_discover_tests(osm_routing_tests)
