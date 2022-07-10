cmake_minimum_required(VERSION 3.22)
project(crud_manzano_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(crud)

add_executable(crud_manzano_cpp
        crud/conio.h
        crud/main.cpp
        crud/manzano.h
        crud/menu.h
        crud/registro.h)
