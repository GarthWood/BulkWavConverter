//
// Courtesy of https://stackoverflow.com/a/22285532 with some modifications
//

#include "Thread.h"

Thread::Thread()
: state(EState_None)
, handle(0)
{
}

Thread::~Thread()
{
    assert(state != EState_Started || joined);
}

void Thread::start()
{
    assert(state == EState_None);

    // in case of thread create error I usually FatalExit...
    if (pthread_create(&handle, nullptr, threadProc, this))
    {
        abort();
    }

    state = EState_Started;
}

void Thread::join()
{
    // A started thread must be joined exactly once!
    // This requirement could be eliminated with an alternative implementation but it isn't needed.
    assert(state == EState_Started);

    pthread_join(handle, nullptr);

    state = EState_Joined;
}

void* Thread::threadProc(void* param)
{
    auto thread = reinterpret_cast<Thread*>(param);

    thread->run();

    return nullptr;
}