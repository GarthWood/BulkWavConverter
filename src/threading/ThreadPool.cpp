//
// Courtesy of https://stackoverflow.com/a/22285532 with some modifications
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(int size)
{
    for (int i = 0; i < size; ++i)
    {
        threads.push_back(new PoolWorkerThread(workQueue));
        threads.back()->start();
    }
}

ThreadPool::~ThreadPool()
{
    finish();
}

void ThreadPool::addTask(ThreadTask *nt)
{
    workQueue.addTask(nt);
}

void ThreadPool::finish()
{
    for (size_t i = 0; i < threads.size(); ++i)
    {
        workQueue.addTask(nullptr);
    }

    for (auto &thread : threads) {
        thread->join();
        delete thread;
    }

    threads.clear();
}
