cmake_minimum_required(VERSION 3.9)
project(BulkWavConverter)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "build/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_ARCHIVE_DIRECTORY "build/${CMAKE_BUILD_TYPE}")

include_directories(lib/lame/include)
include_directories(lib/gtest/include)
include_directories(lib/gmock/include)

IF(WIN32)
    set(LIB_DIRECTORY lib/lame/bin/win lib/gtest/bin/win lib/gmock/bin/win)
    set(APP_LIBS mp3lame.lib)
    set(TEST_LIBS gtest_main.lib gtest.lib gmock_main.a gmock.lib)
ELSE()
    set(LIB_DIRECTORY lib/lame/bin/nix lib/gtest/bin/nix lib/gmock/bin/nix)
    set(APP_LIBS mp3lame.a)
    set(TEST_LIBS gtest_main.a gtest.a gmock_main.a gmock.a)
ENDIF()

link_directories(${LIB_DIRECTORY})

add_executable(BulkWavConverter
        lib/lame/include/lame.h src/Main.cpp src/threading/ThreadPool.cpp src/threading/ThreadPool.h src/Common.h src/threading/Thread.cpp src/threading/Thread.h src/threading/ThreadTask.h src/threading/ThreadWorkQueue.cpp src/threading/ThreadWorkQueue.h src/threading/PoolWorkerThread.cpp src/threading/PoolWorkerThread.h src/Mp3EncoderTask.cpp src/Mp3EncoderTask.h src/services/LameService.cpp src/services/LameService.h src/services/ConsoleLoggingService.cpp src/services/ConsoleLoggingService.h src/wavfile/WavFileEncoder.cpp src/wavfile/WavFileEncoder.h src/wavfile/Encoder.cpp src/wavfile/Encoder.h src/services/DirectoryService.cpp src/services/DirectoryService.h)

add_executable(BulkWavConverterTest test/TestMain.cpp test/ThreadWorkQueueTest.hpp test/ThreadTaskTest.hpp src/threading/ThreadWorkQueue.cpp)

target_link_libraries(BulkWavConverter ${APP_LIBS})
target_link_libraries(BulkWavConverterTest ${TEST_LIBS})
