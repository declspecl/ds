cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(_DEBUG TRUE)

project(ds VERSION 1.0)

add_executable(ds
    src/main.cpp)
