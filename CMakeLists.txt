cmake_minimum_required(VERSION 3.15)
project(rescv)

set(CMAKE_CXX_STANDARD 14)

add_executable(rescv main.cpp init.hpp instructiondecode.hpp execute.hpp memoryaccess.hpp writeback.hpp type.hpp)