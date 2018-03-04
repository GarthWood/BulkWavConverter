/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/22285532
 *
 * A thread pool to manage concurrency
 */

#ifndef BULKWAVCONVERTER_THREADPOOL_H
#define BULKWAVCONVERTER_THREADPOOL_H

#include "../Common.h"
#include "ThreadTask.h"
#include "ThreadWorkQueue.h"
#include "Thread.h"
#include "PoolWorkerThread.h"

class ThreadPool
{
public:
    /**
     * Constructor
     * @param size The maximum number of active threads
     * @param deleteTaskOnComplete Whether the task must be deleted once it completes
     */
    ThreadPool(int size, bool deleteTaskOnComplete = true);

    /**
     * Destructor
     */
    virtual ~ThreadPool();

    /**
     * Add a task
     * @param task The task to add
     */
    void addTask(ThreadTask* task);

    /**
     * Asking the threads to finish, waiting for the task queue to be consumed and then returning.
     */
    void finish();

private:

    vector<PoolWorkerThread*> mThreads;

    ThreadWorkQueue mWorkQueue;
};


#endif // BULKWAVCONVERTER_THREADPOOL_H
