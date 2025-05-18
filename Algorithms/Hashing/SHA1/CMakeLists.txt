cmake_minimum_required(VERSION 3.20)

project(SHA1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(fmt)

add_executable(SHA1 sha1.hpp main.cpp)
target_link_libraries(SHA1 fmt::fmt)
