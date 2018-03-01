//
// Created by Garth on 2018/03/01.
//

#include "LoggingService.h"

LoggingService::LoggingService()
{
    pthread_mutex_init(&mutex, 0);
}

LoggingService::~LoggingService()
{
    pthread_mutex_destroy(&mutex);
}

void LoggingService::log(const char* log, ...)
{
    va_list args;
    va_start(args, log);

    va_list argsCopy;
    va_copy(argsCopy, args);

    int len = vsnprintf(nullptr, 0, log, args);

    if (len >= 0)
    {
        size_t  length = ((size_t) len) + 1;
        char* res = (char*) malloc(length);

        if (res)
        {
            vsnprintf(res, length, log, argsCopy);

            pthread_mutex_lock(&mutex);
            cout << res << endl;
            pthread_mutex_unlock(&mutex);

            free(res);
        }
    }

    va_end(argsCopy);
    va_end(args);
}
