cmake_minimum_required(VERSION 3.13)
project(E01 C)

set(CMAKE_C_STANDARD 11)

add_executable(E01 main.c ST.c ST.h graph.c graph.h DAG.c DAG.h)