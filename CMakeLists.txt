cmake_minimum_required(VERSION 3.10.2)
project(riscv)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Ofast")
set(src_dir
        main.cpp init.hpp instructiondecode.hpp execute.hpp memoryaccess.hpp writeback.hpp type.hpp)
add_executable(code ${src_dir})