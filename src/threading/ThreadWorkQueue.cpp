/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/22285532
 *
 * A queue to hold thread tasks
 */

#include "ThreadWorkQueue.h"

/**
 * Constructor
 */
ThreadWorkQueue::ThreadWorkQueue()
{
    pthread_mutex_init(&mQmtx, 0);

    pthread_cond_init(&mWcond, 0);
}

/**
 * Destructor
 */
ThreadWorkQueue::~ThreadWorkQueue()
{
    pthread_mutex_destroy(&mQmtx);
    pthread_cond_destroy(&mWcond);
}

/**
 * Retrieves the next task from the queue
 * @return The task at the front of the queue
 */
ThreadTask* ThreadWorkQueue::nextTask()
{
    ThreadTask* task = nullptr;

    pthread_mutex_lock(&mQmtx);

    while (mTasks.empty())
    {
        pthread_cond_wait(&mWcond, &mQmtx);
    }

    task = mTasks.front();
    mTasks.pop();

    pthread_mutex_unlock(&mQmtx);

    return task;
}

/**
 * Add a task
 * @param task The task to add
 */
void ThreadWorkQueue::addTask(ThreadTask* task)
{
    pthread_mutex_lock(&mQmtx);

    mTasks.push(task);

    pthread_cond_signal(&mWcond);

    pthread_mutex_unlock(&mQmtx);
}
