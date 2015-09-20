cmake_minimum_required(VERSION 3.3)
project(CS263hw1part2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main-wp.cpp WordPuzzleSolver.cpp WordPuzzleSolver.h)
add_executable(CS263hw1part2 ${SOURCE_FILES})