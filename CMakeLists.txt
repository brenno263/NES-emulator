cmake_minimum_required(VERSION 3.21)
project(NES)

set(CMAKE_CXX_STANDARD 14)

add_executable(NES main.cpp Bus.cpp Bus.h Cpu.cpp Cpu.h)
