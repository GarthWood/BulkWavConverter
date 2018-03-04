/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/22285532
 *
 * A thread pool worker
 */

#include "PoolWorkerThread.h"

/**
 * Constructor
 * @param workQueue The threading work queue
 * @param deleteTaskOnComplete Whether the task must be deleted once it completes
 */
PoolWorkerThread::PoolWorkerThread(ThreadWorkQueue& workQueue, bool deleteTaskOnComplete)
: mWorkQueue(workQueue)
, mDeleteTaskOnComplete(deleteTaskOnComplete)
{
}


/****************************************************************************
 * Protected Methods
****************************************************************************/

/**
 * Executes the pool task
 */
void PoolWorkerThread::run()
{
    while (ThreadTask* task = mWorkQueue.nextTask())
    {
        task->run();

        if (mDeleteTaskOnComplete)
        {
            delete task;
        }
    }
}
