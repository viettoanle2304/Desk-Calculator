cmake_minimum_required(VERSION 3.17)
project(Desk_Calculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Desk_Calculator main.cpp utility.cpp utility.h Stack.cpp Stack.h error_code.h)