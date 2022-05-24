cmake_minimum_required(VERSION 3.21)
project(cpp_FindMaxGraphPart)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)

find_package(MPI REQUIRED)

add_executable(cpp_FindMaxGraphPart main.cpp Graph.cpp Graph.h GraphWorker.cpp GraphWorker.h SharedQueue.h)
target_link_libraries(cpp_FindMaxGraphPart PUBLIC MPI::MPI_CXX)
