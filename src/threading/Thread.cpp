/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/22285532
 *
 * A thread container
 */

#include "Thread.h"

/**
 * Constructor
 */
Thread::Thread()
: mState(EState_None)
{
}

/**
 * Destructor
 */
Thread::~Thread()
{
}

/**
 * Starts the thread
 */
void Thread::start()
{
    if (pthread_create(&mHandle, nullptr, threadProc, this))
    {
        abort();
    }

    mState = EState_Started;
}

/**
 * Causes the calling thread to block until this thread completes
 */
void Thread::join()
{
    pthread_join(mHandle, nullptr);

    mState = EState_Joined;
}


/****************************************************************************
 * Private Methods
****************************************************************************/

/**
 * Initiates the thread
 * @param param The thread paramter
 * @return A thread parameter
 */
void* Thread::threadProc(void* param)
{
    auto thread = reinterpret_cast<Thread*>(param);

    thread->run();

    return nullptr;
}
