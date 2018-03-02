cmake_minimum_required(VERSION 3.9)
project(BulkWavConverter)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "build/$(CMAKE_BUILD_TYPE)")
set(CMAKE_LIBRARY_ARCHIVE_DIRECTORY "build/$(CMAKE_BUILD_TYPE)")

include_directories(lib/lame/include)
link_directories(lib/lame/bin/osx)

add_executable(BulkWavConverter
        lib/lame/include/lame.h src/Main.cpp src/threading/ThreadPool.cpp src/threading/ThreadPool.h src/Common.h src/threading/Thread.cpp src/threading/Thread.h src/threading/ThreadTask.h src/threading/ThreadWorkQueue.cpp src/threading/ThreadWorkQueue.h src/threading/PoolWorkerThread.cpp src/threading/PoolWorkerThread.h src/Mp3EncoderTask.cpp src/Mp3EncoderTask.h src/services/LameService.cpp src/services/LameService.h src/services/LoggingService.cpp src/services/LoggingService.h src/wavfile/WavFileEncoder.cpp src/wavfile/WavFileEncoder.h src/wavfile/Encoder.cpp src/wavfile/Encoder.h src/services/DirectoryService.cpp src/services/DirectoryService.h)

target_link_libraries(BulkWavConverter mp3lame.a)