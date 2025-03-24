cmake_minimum_required(VERSION 3.30)
project(DevOps_mine)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(DevOps_mine
    src/main.cpp
        src/ReadFasta.cpp
        src/ReadFasta.hpp
        src/ReadFastq.cpp
        src/ReadFastq.hpp
        src/Sequence.cpp
        src/Sequence.hpp)
