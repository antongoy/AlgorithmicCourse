cmake_minimum_required(VERSION 3.5)
project(MinSpanningTree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp
                 src/DisjointSetUnion.cpp
                 src/DisjointSetUnion.hpp
                 src/Edge.hpp
                 src/merge_sort.hpp
                 src/kruskal.cpp
                 src/kruskal.hpp)

add_executable(MinSpanningTree ${SOURCE_FILES})