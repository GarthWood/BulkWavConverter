//
// Courtesy of https://stackoverflow.com/a/22285532 with some modifications
//

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
    ThreadPool(int size);
    virtual ~ThreadPool();

    /**
     * Add a task
     * @param nt The task to add
     */
    void addTask(ThreadTask *nt);

    /**
     * Asking the threads to finish, waiting for the task queue to be consumed and then returning.
     */
    void finish();

private:

    vector<PoolWorkerThread*> threads;

    ThreadWorkQueue workQueue;
};


#endif //BULKWAVCONVERTER_THREADPOOL_H
