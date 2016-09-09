cmake_minimum_required(VERSION 2.8)
project(cppIPC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include(cmake/IdentifyPlatform.cmake)
include_directories(include)

add_subdirectory(LockF)
add_subdirectory(Pipes)
add_subdirectory(RaceCondition)
add_subdirectory(SharedMemory)
