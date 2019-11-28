cmake_minimum_required(VERSION 3.13)
project(E03 C)

set(CMAKE_C_STANDARD 11)

add_executable(E03 main.c calculators.c calculators.h indexTable.c indexTable.h adj.c adj.h)