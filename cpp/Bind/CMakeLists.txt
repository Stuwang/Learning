cmake_minimum_required(VERSION 2.8)

set( CMAKE_EXPORT_COMPILE_COMMANDS ON ) 

add_definitions(-std=c++14)


add_executable(main main.cpp)

add_executable(test test.cpp)
