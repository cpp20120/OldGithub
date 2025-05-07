cmake_minimum_required(VERSION 3.23)
project(Intersect_master)

set(CMAKE_CXX_STANDARD 14)

add_executable(Parametric src/main.cpp src/Segment3d.h src/Segment3Dext.h src/Vector3D.h src/NumComp.h)