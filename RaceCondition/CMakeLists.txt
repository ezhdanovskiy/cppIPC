cmake_minimum_required(VERSION 3.5)
project(RaceCondition)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(RaceCondition main.cpp)