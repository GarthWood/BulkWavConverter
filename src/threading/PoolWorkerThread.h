//
// Courtesy of https://stackoverflow.com/a/22285532 with some modifications
//

#ifndef BULKWAVCONVERTER_POOLWORKERTHREAD_H
#define BULKWAVCONVERTER_POOLWORKERTHREAD_H

#include "Thread.h"
#include "ThreadTask.h"
#include "ThreadWorkQueue.h"

class PoolWorkerThread : public Thread
{
public:
    PoolWorkerThread(ThreadWorkQueue& _work_queue, bool deleteTaskOnComplete = true);

protected:

    virtual void run();

private:

    ThreadWorkQueue& work_queue;

    bool deleteOnComplete;
};


#endif //BULKWAVCONVERTER_POOLWORKERTHREAD_H
