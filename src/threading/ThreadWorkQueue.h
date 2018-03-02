/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/22285532
 *
 * A queue to hold thread tasks
 */

#ifndef BULKWAVCONVERTER_THREADWORKQUEUE_H
#define BULKWAVCONVERTER_THREADWORKQUEUE_H

#include "ThreadTask.h"
#include <queue>
#include <unistd.h>
#include <pthread.h>

class ThreadWorkQueue
{
public:
    /**
     * Constructor
     */
    ThreadWorkQueue();

    /**
     * Destructor
     */
    virtual ~ThreadWorkQueue();

    /**
     * Retrieves the next task from the queue
     * @return The task at the front of the queue
     */
    ThreadTask* nextTask();

    /**
     * Add a task
     * @param task The task to add
     */
    void addTask(ThreadTask* task);

private:

    std::queue<ThreadTask*> mTasks;

    pthread_mutex_t mQmtx;

    pthread_cond_t mWcond;
};


#endif // BULKWAVCONVERTER_THREADWORKQUEUE_H
