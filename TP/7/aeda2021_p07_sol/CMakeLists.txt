cmake_minimum_required(VERSION 3.10)
project(aeda2021_p07_sol)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Tests")

add_executable(aeda2021_p07_sol main.cpp Tests/tests.cpp Tests/binaryTree.h Tests/bst.h Tests/dictionary.cpp Tests/game.cpp)

target_link_libraries(aeda2021_p07_sol gtest gtest_main)
