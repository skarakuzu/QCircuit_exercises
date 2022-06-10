cmake_minimum_required(VERSION 3.0)
project(main LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -Wall")

add_executable(${PROJECT_NAME}  main.cpp )








