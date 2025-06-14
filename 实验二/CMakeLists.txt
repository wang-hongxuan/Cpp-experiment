cmake_minimum_required(VERSION 3.30)
project(2024337621070)

set(CMAKE_CXX_STANDARD 20)

add_executable(2024337621070 main.cpp
        User.cpp
        User.h
        Administrator.cpp
        Administrator.h
        Teacher.cpp
        Teacher.h
        Student.cpp
        Student.h
        Course.cpp
        Course.h
        ConsoleUtils.h
        StudentDB.cpp
        StudentDB.h)
