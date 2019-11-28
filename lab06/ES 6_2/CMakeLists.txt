cmake_minimum_required(VERSION 3.12)
project(ES_6_2 C)

set(CMAKE_C_STANDARD 99)

add_executable(ES_6_2 main.c)

configure_file(anagrafiche.txt anagrafiche.txt COPYONLY)