cmake_minimum_required(VERSION 3.14)

project(hash-hash)

set(SRC_LIST hash-hash.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors -gdwarf-4 -std=c++20")

add_executable(${PROJECT_NAME} ${SRC_LIST})

