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

#include "ThreadTask.h"
#include "ThreadWorkQueue.h"
#include "Thread.h"
#include "PoolWorkerThread.h"

using namespace std;

class ThreadPool
{
public:
    /**
     * Constructor
     */
    ThreadPool(int size);

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
