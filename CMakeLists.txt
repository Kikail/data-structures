cmake_minimum_required(VERSION 4.3)
project(data_structures C)

set(CMAKE_C_STANDARD 11)

set(PROJECT_SOURCES
        src/hashtable/hashtable.h
        src/hashtable/hashtable.c
)

include_directories(.)
include_directories(src)
include_directories(src/hashtable)

add_executable(hashtables testing/test_hashtable.c ${PROJECT_SOURCES})