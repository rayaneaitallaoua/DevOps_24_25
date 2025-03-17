cmake_minimum_required(VERSION 3.30)
project(DevOps_mine)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(DevOps_mine
    src/main.cpp
    src/ReadFasta.cpp
    src/ReadFasta.h
    src/ReadFastq.cpp
    src/ReadFastq.h
    src/Sequence.cpp
    src/Sequence.h)
