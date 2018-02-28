cmake_minimum_required(VERSION 3.9)
project(BulkWavConverter)

set(CMAKE_CXX_STANDARD 11)

add_executable(BulkWavConverter
        lib/lame/include/lame.h src/Main.cpp)
