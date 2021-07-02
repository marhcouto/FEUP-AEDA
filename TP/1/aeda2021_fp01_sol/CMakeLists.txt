cmake_minimum_required(VERSION 3.10)
project(aeda2021_fp01_sol)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(aeda2021_fp01_sol main.cpp Tests/tests.cpp Tests/parque.cpp)

target_link_libraries(aeda2021_fp01_sol gtest gtest_main)
