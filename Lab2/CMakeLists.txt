cmake_minimum_required(VERSION 3.6)
project(Lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/utils.h)
add_executable(Lab2 ${SOURCE_FILES})