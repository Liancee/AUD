cmake_minimum_required(VERSION 3.26)
project(exercises C)

set(CMAKE_C_STANDARD 11)

add_executable(exercises main.c
        menu.c
        tools.c
        datetime.c
        calendar.c
        database.c
        database.h)
