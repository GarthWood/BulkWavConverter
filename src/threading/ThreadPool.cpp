/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/22285532
 *
 * A thread pool to manage concurrency
 */

#include "ThreadPool.h"

/**
 * Constructor
 * @param size The maximum number of active threads
 * @param deleteTaskOnComplete Whether the task must be deleted once it completes
 */
ThreadPool::ThreadPool(int size, bool deleteTaskOnComplete/* = true*/)
{
    for (int i = 0; i < size; ++i)
    {
        mThreads.push_back(new PoolWorkerThread(mWorkQueue, deleteTaskOnComplete));
        mThreads.back()->start();
    }
}

/**
 * Destructor
 */
ThreadPool::~ThreadPool()
{
    finish();
}

/**
 * Add a task
 * @param task The task to add
 */
void ThreadPool::addTask(ThreadTask *task)
{
    mWorkQueue.addTask(task);
}

/**
 * Asking the threads to finish, waiting for the task queue to be consumed and then returning.
 */
void ThreadPool::finish()
{
    for (size_t i = 0; i < mThreads.size(); ++i)
    {
        mWorkQueue.addTask(nullptr);
    }

    for (auto &thread : mThreads) {
        thread->join();
        delete thread;
    }

    mThreads.clear();
}
