cmake_minimum_required(VERSION 3.5)
project(cppIPC)

include_directories(include)

add_subdirectory(RaceCondition)
add_subdirectory(SharedMemory)
add_subdirectory(Pipes)
