cmake_minimum_required(VERSION 3.26)
project(oop_a4_5_cotoirares)

set(CMAKE_CXX_STANDARD 14)

include_directories(domain)
include_directories(repository)
include_directories(service)
include_directories(ui)

add_executable(oop_a4_5_cotoirares
        domain/dynamic_array.h
        repository/repo.cpp
        repository/repo.h
        service/service.cpp
        service/service.h
        ui/ui.cpp
        ui/ui.h
        main.cpp
        domain/movie.h
        domain/movie.cpp)
