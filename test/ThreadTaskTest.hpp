//
// Created by Garth on 2018/03/02.
//

#ifndef BULKWAVCONVERTER_THREADTASKTEST_H
#define BULKWAVCONVERTER_THREADTASKTEST_H

#include <string>

#include "../src/threading/ThreadTask.h"

using namespace std;

class ThreadTaskTest : public ThreadTask
{
public:
    ThreadTaskTest(const char* name) : ThreadTask()
    {
        mName = name;
    }

    const char* getName() const { return mName.c_str(); }

protected:

    virtual void run() {}

private:

    string mName;
};

#endif //BULKWAVCONVERTER_THREADTASKTEST_H
