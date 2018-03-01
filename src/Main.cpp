//
// Created by Garth on 2018/02/28.
// Entry point into the application
//

#include <stdio.h>
#include <iostream>
#include "Common.h"
#include "threading/ThreadPool.h"
#include "services/LameService.h"
#include "services/LoggingService.h"
#include "Mp3EncoderTask.h"

using namespace std;

int main(int argc, char* args[])
{
    LameService lameService;
    LoggingService loggingService;

    ThreadPool threadPool(DEFAULT_THREAD_COUNT);

    threadPool.addTask(new Mp3EncoderTask("testfiles/368024__warrior5445__song.wav", "testfiles/368024__warrior5445__song.mp3", &lameService, &loggingService));
    threadPool.addTask(new Mp3EncoderTask("testfiles/386469__ben-stone__harambe-the-bush-kangaroostart.wav", "testfiles/386469__ben-stone__harambe-the-bush-kangaroostart.mp3", &lameService, &loggingService));
    threadPool.addTask(new Mp3EncoderTask("testfiles/391538__mativve__cheerful-song.wav", "testfiles/391538__mativve__cheerful-song.mp3", &lameService, &loggingService));
    threadPool.addTask(new Mp3EncoderTask("testfiles/largefile.wav", "testfiles/largefile1.mp3", &lameService, &loggingService));
//    threadPool.addTask(new Mp3EncoderTask("testfiles/largefile.wav", "testfiles/largefile2.mp3", &lameService, &loggingService));
//    threadPool.addTask(new Mp3EncoderTask("testfiles/largefile.wav", "testfiles/largefile3.mp3", &lameService, &loggingService));

    return 0;
}