//
// Courtesy of https://stackoverflow.com/a/22285532 with some modifications
//

#ifndef BULKWAVCONVERTER_THREADWORKQUEUE_H
#define BULKWAVCONVERTER_THREADWORKQUEUE_H

#include "ThreadTask.h"
#include <queue>
#include <unistd.h>
#include <pthread.h>

class ThreadWorkQueue
{
public:
    ThreadWorkQueue();
    virtual ~ThreadWorkQueue();

    /**
     * Retrieves the next task from the queue
     */
    ThreadTask* nextTask();

    /**
     * Add a task
     */
    void addTask(ThreadTask *nt);

private:

    std::queue<ThreadTask*> tasks;

    pthread_mutex_t qmtx;

    pthread_cond_t wcond;
};


#endif //BULKWAVCONVERTER_THREADWORKQUEUE_H
