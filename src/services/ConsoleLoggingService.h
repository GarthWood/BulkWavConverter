/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * A service to log to the console
 */

#ifndef BULKWAVCONVERTER_LOGGINGSERVICE_H
#define BULKWAVCONVERTER_LOGGINGSERVICE_H

#include "../Common.h"

class ConsoleLoggingService
{
public:
    /**
     * Constructor
     */
    ConsoleLoggingService();

    /**
     * Destructor
     */
    virtual ~ConsoleLoggingService();

    /**
     * Logs the specified message to the console
     * @param log The log format
     * @param ... The log params
     */
    void log(const char* log, ...);

private:

    pthread_mutex_t mMutex;
};

typedef ConsoleLoggingService* LoggingServicePtr;

#endif // BULKWAVCONVERTER_LOGGINGSERVICE_H
