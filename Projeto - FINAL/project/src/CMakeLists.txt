cmake_minimum_required(VERSION 3.17)
project(untitled2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(untitled2 main.cpp Portagem.cpp Portagem.h Way.cpp Way.h Worker.cpp Worker.h CentralPortagens.cpp CentralPortagens.h Vehicle.cpp Vehicle.h HighWay.cpp HighWay.h Exceptions.h FileHandling.h Intervention.cpp Intervention.h BST.h Utilities.h)