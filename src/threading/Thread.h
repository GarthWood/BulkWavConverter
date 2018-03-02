/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/22285532
 *
 * A thread container
 */

#ifndef BULKWAVCONVERTER_THREAD_H
#define BULKWAVCONVERTER_THREAD_H

#include <pthread.h>
#include <assert.h>

using namespace std;

class Thread
{
public:
    /**
     * Constructor
     */
    Thread();

    /**
     * Destructor
     */
    virtual ~Thread();

    /**
     * Starts the thread
     */
    void start();

    /**
     * Causes the calling thread to block until this thread completes
     */
    void join();

protected:

    /**
     * Executes the thread
     */
    virtual void run() = 0;

private:

    /**
     * Initiates the thread
     * @param param The thread paramter
     * @return A thread parameter
     */
    static void* threadProc(void* param);

private:

    /**
     * Thread states
     */
    enum EState
    {
        EState_None,
        EState_Started,
        EState_Joined
    };

    EState mState;

    bool mJoined;

    pthread_t mHandle;
};


#endif // BULKWAVCONVERTER_THREAD_H
