/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/22285532
 *
 * A thread pool worker
 */

#ifndef BULKWAVCONVERTER_POOLWORKERTHREAD_H
#define BULKWAVCONVERTER_POOLWORKERTHREAD_H

#include "../Common.h"
#include "Thread.h"
#include "ThreadTask.h"
#include "ThreadWorkQueue.h"

class PoolWorkerThread : public Thread
{
public:
    /**
     * Constructor
     * @param workQueue The threading work queue
     * @param deleteTaskOnComplete Whether the task must be delete once it completes
     */
    PoolWorkerThread(ThreadWorkQueue& workQueue, bool deleteTaskOnComplete = true);

protected:

    /**
     * Executes the pool task
     */
    virtual void run();

private:

    ThreadWorkQueue& mWorkQueue;

    bool mDeleteTaskOnComplete;
};


#endif // BULKWAVCONVERTER_POOLWORKERTHREAD_H
