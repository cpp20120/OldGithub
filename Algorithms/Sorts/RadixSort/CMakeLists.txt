cmake_minimum_required(VERSION 3.20)

project(Radix)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt)

add_executable(Radix sort.hpp main.cpp)
target_link_libraries(Radix fmt::fmt)