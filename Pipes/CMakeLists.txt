cmake_minimum_required(VERSION 3.5)
project(Pipes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(Pipes main.cpp)
