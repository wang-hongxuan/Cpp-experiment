cmake_minimum_required(VERSION 3.30)
project(shiyan)

set(CMAKE_CXX_STANDARD 11)

add_executable(shiyan main.cpp
        src/Course.cpp
        src/Course.h
        src/Student.cpp
        src/Student.h)
