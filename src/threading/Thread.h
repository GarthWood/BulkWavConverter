//
// Courtesy of https://stackoverflow.com/a/22285532 with some modifications
//

#ifndef BULKWAVCONVERTER_THREAD_H
#define BULKWAVCONVERTER_THREAD_H

#include <pthread.h>
#include <assert.h>

using namespace std;

class Thread
{
public:
    Thread();
    virtual ~Thread();

    void start();

    void join();

protected:

    virtual void run() = 0;

private:

    static void* threadProc(void* param);

private:
    enum EState
    {
        EState_None,
        EState_Started,
        EState_Joined
    };

    EState state;

    bool joined;

    pthread_t handle;
};


#endif //BULKWAVCONVERTER_THREAD_H
