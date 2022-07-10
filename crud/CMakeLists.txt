cmake_minimum_required(VERSION 3.22)
project(crud)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(crud
        main.cpp
        manzano.h
        menu.h
        registro.h)
