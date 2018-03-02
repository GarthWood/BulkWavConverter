cmake_minimum_required(VERSION 3.9)
project(BulkWavConverter)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "build/${CMAKE_BUILD_TYPE}")
set(CMAKE_LIBRARY_ARCHIVE_DIRECTORY "build/${CMAKE_BUILD_TYPE}")

include_directories(lib/lame/include)
include_directories(lib/gtest/include)
include_directories(lib/gmock/include)

IF(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-DMSVC_RUNTIME=static)
    set(LIB_DIRECTORY lib/pthreads_win32/bin lib/lame/bin/win lib/gtest/bin/win lib/gmock/bin/win)
    set(APP_LIBS mp3lame.lib mpghip.lib pthreadVC2_x86.lib)
    set(TEST_LIBS gtest_maind.lib gtestd.lib gmock_maind.lib gmockd.lib pthreadVC2_x86.lib)
    include_directories(lib/pthreads_win32/include lib/dirent/include)
ELSE()
    IF(APPLE)
        set(LIB_DIRECTORY lib/lame/bin/osx lib/gtest/bin/osx lib/gmock/bin/osx)
    ELSE()
        set(LIB_DIRECTORY lib/lame/bin/linux lib/gtest/bin/linux lib/gmock/bin/linux)
    ENDIF()
    set(APP_LIBS pthread mp3lame)
    set(TEST_LIBS pthread gtest_main gtest gmock_main gmock)
ENDIF()

link_directories(${LIB_DIRECTORY})

add_executable(BulkWavConverter
        lib/lame/include/lame.h src/Main.cpp src/threading/ThreadPool.cpp src/threading/ThreadPool.h src/Common.h src/threading/Thread.cpp src/threading/Thread.h src/threading/ThreadTask.h src/threading/ThreadWorkQueue.cpp src/threading/ThreadWorkQueue.h src/threading/PoolWorkerThread.cpp src/threading/PoolWorkerThread.h src/Mp3EncoderTask.cpp src/Mp3EncoderTask.h src/services/LameService.cpp src/services/LameService.h src/services/ConsoleLoggingService.cpp src/services/ConsoleLoggingService.h src/wavfile/WavFileEncoder.cpp src/wavfile/WavFileEncoder.h src/wavfile/Encoder.cpp src/wavfile/Encoder.h src/services/DirectoryService.cpp src/services/DirectoryService.h)

add_executable(BulkWavConverterTest test/TestMain.cpp test/ThreadWorkQueueTest.hpp test/ThreadTaskTest.hpp src/threading/ThreadWorkQueue.cpp)

IF(MSVC)
    set_target_properties(BulkWavConverterTest PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
ENDIF()

target_link_libraries(BulkWavConverter ${APP_LIBS})
target_link_libraries(BulkWavConverterTest ${TEST_LIBS})
