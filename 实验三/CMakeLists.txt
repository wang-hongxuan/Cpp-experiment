cmake_minimum_required(VERSION 3.30)
project(3)

set(CMAKE_CXX_STANDARD 20)

add_executable(3 main.cpp
        Administrator.cpp
        Administrator.h
        Student.cpp
        Student.h
        Teacher.cpp
        Teacher.h
        User.cpp
        User.h
        Course.cpp
        Course.h
        ConsoleUtils.h
)
