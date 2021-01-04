cmake_minimum_required(VERSION 3.17)
project(client C)

set(CMAKE_C_STANDARD 11)

include_directories(inc)

add_executable(client
        inc/client.h
        src/handler.c
        src/main.c)
