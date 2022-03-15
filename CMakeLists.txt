cmake_minimum_required(VERSION 3.21)
project(cpp_FindMaxGraphPart)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpp_FindMaxGraphPart main.cpp Graph.cpp Graph.h GraphWorker.cpp GraphWorker.h)
