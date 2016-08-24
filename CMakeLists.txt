cmake_minimum_required(VERSION 3.5)
project(cppSharedMemory)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp)
add_executable(cppSharedMemory ${SOURCE_FILES})