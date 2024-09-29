cmake_minimum_required(VERSION 3.26)
project(oop_t2_cotoirares)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(oop_t2_cotoirares
        Car.cpp
        Car.h
        Engine.cpp
        Engine.h
        main.cpp
        Service.cpp
        Service.h
        ui.cpp
        ui.h)
