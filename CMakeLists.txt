cmake_minimum_required(VERSION 3.23)
project(ExoticSorting)

set(CMAKE_CXX_STANDARD 14)

add_executable(ExoticSorting main.cpp ParallelCountingSort.h Constants.h)
