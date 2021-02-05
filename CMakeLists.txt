cmake_minimum_required(VERSION 3.17)
project(my6502 C)

set(CMAKE_C_STANDARD 99)

add_executable(my6502 main.c cpu.c mem.c)
