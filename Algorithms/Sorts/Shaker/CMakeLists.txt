cmake_minimum_required(VERSION 3.20)

project(Shaker)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(Shaker sort.hpp main.cpp)
