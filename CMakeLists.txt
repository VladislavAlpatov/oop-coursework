cmake_minimum_required(VERSION 3.24)
project(oop_coursework)

set(CMAKE_CXX_STANDARD 23)

add_executable(oop_coursework main.cpp)
target_sources(oop_coursework PRIVATE CBase.cpp CApplication.cpp CBase2.cpp)
