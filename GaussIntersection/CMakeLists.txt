cmake_minimum_required(VERSION 3.23)
project(Intersect)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/Matrix3D)
include_directories(src/Matrix4x4)

add_executable(Intersect
        src/Matrix3D/Matrix3D.h
        src/Matrix3D/SysLinearEquat3D.h
        src/Matrix4x4/Matrix4x4.h
        src/Matrix4x4/SysLinearEquat3D.h
        src/Exeption.h
        src/main.cpp
        src/Matrix3D.h
        src/NumComp.h
        src/Segment3d.h
        src/Vector3D.h)
