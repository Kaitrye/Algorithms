cmake_minimum_required(VERSION 3.0)
project(battle)

set(SOURCES battle.cpp cards.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pedantic-errors -gdwarf-4")

add_executable(${PROJECT_NAME} ${SOURCES})

