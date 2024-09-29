cmake_minimum_required(VERSION 3.26)
project(a2_3_cotoirares C)

set(CMAKE_C_STANDARD 11)

add_executable(a2_3_cotoirares
        main.c
        UI/UI.h
        UI/UI.c
        repository/memory_repo.h
        repository/memory_repo.c
        domain/domain.h
        domain/domain.c
        controller/controller.h
        controller/controller.c
        tests.c)
