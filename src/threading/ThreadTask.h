/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/22285532
 *
 * An abstract class describing the task contract
 */

#ifndef BULKWAVCONVERTER_THREADTASK_H
#define BULKWAVCONVERTER_THREADTASK_H

class ThreadTask
{
public:
    /**
     * Constructor
     */
    ThreadTask() {}

    /**
     * Destructor
     */
    virtual ~ThreadTask() {}

    /**
     * Executes the task
     */
    virtual void run() = 0;
};

#endif // BULKWAVCONVERTER_THREADTASK_H
