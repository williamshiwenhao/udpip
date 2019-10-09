cmake_minimum_required(VERSION 3.14)
project(udpip)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(udpip
        jsoncpp.cpp
        main.cpp
        udp.cpp
        udpip.cpp)

add_executable(udp_server
        udp_server.cpp
        udp.cpp
        jsoncpp.cpp
        )
