//
// Created by Garth on 2018/03/01.
//

#include "ConsoleLoggingService.h"

/**
 * Constructor
 */
ConsoleLoggingService::ConsoleLoggingService()
{
    pthread_mutex_init(&mMutex, 0);
}

/**
 * Destructor
 */
ConsoleLoggingService::~ConsoleLoggingService()
{
    pthread_mutex_destroy(&mMutex);
}

/**
 * Logs the specified message to the console
 * @param log The log format
 * @param ... The log params
 */
void ConsoleLoggingService::log(const char* log, ...)
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

            pthread_mutex_lock(&mMutex);
            cout << res << endl;
            pthread_mutex_unlock(&mMutex);

            free(res);
        }
    }

    va_end(argsCopy);
    va_end(args);
}
