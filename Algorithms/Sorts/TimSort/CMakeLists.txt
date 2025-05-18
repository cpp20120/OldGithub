cmake_minimum_required(VERSION 3.20)

project(TimSort)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt)

add_executable(TimSort sort.hpp main.cpp)
target_link_libraries(TimSort fmt::fmt)