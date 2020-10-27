cmake_minimum_required(VERSION 3.17)
project(multiplication)

set(CMAKE_CXX_STANDARD 14)

add_executable(multiplication grandentier.cpp multiplication.cpp tests.cpp)