/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * A test task
 */

#ifndef BULKWAVCONVERTER_THREADTASKTEST_H
#define BULKWAVCONVERTER_THREADTASKTEST_H

#include <string>

#include "../src/threading/ThreadTask.h"

using namespace std;

class ThreadTaskTest : public ThreadTask
{
public:
    /**
     * Constructor
     * @param name The name of the task
     */
    ThreadTaskTest(const char* name) : ThreadTask()
    {
        mName = name;
    }

    /**
     * Returns the name of the task
     * @return The name of the task
     */
    const char* getName() const { return mName.c_str(); }

protected:

    /**
     * Executes the task
     */
    virtual void run() {}

private:

    string mName;
};

#endif // BULKWAVCONVERTER_THREADTASKTEST_H
