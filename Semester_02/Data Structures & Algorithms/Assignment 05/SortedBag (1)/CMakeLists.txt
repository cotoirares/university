cmake_minimum_required(VERSION 3.26)
project(SortedBag__1_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SortedBag__1_
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedBag.cpp
        SortedBag.h
        SortedBagIterator.cpp
        SortedBagIterator.h)
