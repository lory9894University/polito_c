cmake_minimum_required(VERSION 3.12)
project(Es_6_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Es_6_1 main.c)

configure_file(grafo.txt grafo.txt COPYONLY)