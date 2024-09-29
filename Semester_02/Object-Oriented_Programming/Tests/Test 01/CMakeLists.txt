cmake_minimum_required(VERSION 3.26)
project(t1_cotoirares_1)

set(CMAKE_CXX_STANDARD 14)

include_directories(domain)
include_directories(repo)
include_directories(service)
include_directories(ui)

add_executable(t1_cotoirares_1
        domain/domain.cpp
        domain/domain.h
        domain/DynamicArray.cpp
        domain/DynamicArray.h
        repo/repo.cpp
        repo/repo.h
        service/service.cpp
        service/service.h
        ui/ui.cpp
        ui/ui.h
        main.cpp
        tests.cpp)
