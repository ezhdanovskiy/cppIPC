cmake_minimum_required(VERSION 2.8)
project(Pipes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(Pipes main.cpp)
if(PLATFORM_BSD)
    target_link_libraries(Pipes iconv)
endif(PLATFORM_BSD)