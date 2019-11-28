cmake_minimum_required(VERSION 3.12)
project(Es_7_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Es_7_1 main.c)

configure_file(gioielli.txt gioielli.txt COPYONLY)