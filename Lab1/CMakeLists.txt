cmake_minimum_required(VERSION 3.5.1)
project(Lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")


add_executable(Lab1 src/main.cpp src/nearest_points.cpp src/nearest_points.hpp src/util.hpp src/util.cpp src/merge_sort.hpp)
