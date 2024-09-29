cmake_minimum_required(VERSION 3.28)
project(oop-e-retake-cotoirares)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/Users/rares/Qt/6.7.1/Src/cmake/")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(oop-e-retake-cotoirares main.cpp
        window.h
        window.cpp
        observer.h
        subject.h
        session.h
        repository.h
        domain.h)

target_link_libraries(oop-e-retake-cotoirares
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

