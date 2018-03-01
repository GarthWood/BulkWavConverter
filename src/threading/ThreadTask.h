//
// Courtesy of https://stackoverflow.com/a/22285532 with some modifications
//

#ifndef BULKWAVCONVERTER_THREADTASK_H
#define BULKWAVCONVERTER_THREADTASK_H

class ThreadTask
{
public:
    ThreadTask() {}
    virtual ~ThreadTask() {}

    virtual void run() = 0;
};

#endif //BULKWAVCONVERTER_THREADTASK_H
