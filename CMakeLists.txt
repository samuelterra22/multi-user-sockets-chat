cmake_minimum_required(VERSION 3.14)
project(multi-user-sockets-chat C)

set(CMAKE_C_STANDARD 99)

## Use onde IDE !!
add_executable(multi-user-sockets-chat server/source/main.c)