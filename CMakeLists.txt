cmake_minimum_required(VERSION 3.27)
project(P11_LRU_Cache)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(P11_LRU_Cache
        LRUCache.cpp
        LRUCache.h
        main.cpp
        test.cpp
        test.h)
