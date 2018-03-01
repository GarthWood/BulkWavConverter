//
// Courtesy of https://stackoverflow.com/a/22285532 with some modifications
//

#include "PoolWorkerThread.h"

PoolWorkerThread::PoolWorkerThread(ThreadWorkQueue& _work_queue, bool deleteTaskOnComplete/* = true*/)
: work_queue(_work_queue)
, deleteOnComplete(deleteTaskOnComplete)
{

}

void PoolWorkerThread::run()
{
    while (ThreadTask* task = work_queue.nextTask())
    {
        task->run();

        if (deleteOnComplete)
        {
            delete task;
        }
    }
}
