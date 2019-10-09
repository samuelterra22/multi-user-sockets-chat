cmake_minimum_required(VERSION 3.14)
project(multi-user-sockets-chat C)

set(CMAKE_C_STANDARD 99)

## Use only IDE !!
add_executable(multi-user-sockets-chat
        server/source/main.c
        client/source/main.c

        lib/list/list.c
        lib/list/list.h

        lib/message/message.c
        lib/message/message.h

        lib/client/client.c
        lib/client/client.h
        )
