//
// Created by Garth on 2018/03/01.
//

#ifndef BULKWAVCONVERTER_LOGGINGSERVICE_H
#define BULKWAVCONVERTER_LOGGINGSERVICE_H

#include <pthread.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class LoggingService {

public:
    LoggingService();
    virtual ~LoggingService();

    void log(const char* log, ...);

private:

    pthread_mutex_t mutex;
};

typedef LoggingService* LoggingServicePtr;

#endif //BULKWAVCONVERTER_LOGGINGSERVICE_H
