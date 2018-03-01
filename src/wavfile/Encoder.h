//
// Created by Garth on 2018/03/01.
//

#ifndef BULKWAVCONVERTER_ENCODER_H
#define BULKWAVCONVERTER_ENCODER_H

#include <lame.h>
#include <queue>
#include "../Common.h"
#include "../threading/Thread.h"
#include "WavFileEncoder.h"

using namespace std;

class Encoder : public Thread
{
public:

    struct stChunk
    {
        int16_t* buffer;
        int size;
    };

public:
    Encoder(const char* outputFilename, int sampleRate, int numChannels, LameService* lameService);
    virtual ~Encoder();

    virtual void run();

    void addChunk(stChunk *chunk);

    void complete();

private:

    void encode(stChunk* chunk);

private:

    FILE* _outputFile;

    queue<stChunk*> _chunks;

    lame_t _lame;

    LameService* _lameService;

    atomic_bool running;

    pthread_mutex_t mutex;

    int _numChannels;
};


#endif //BULKWAVCONVERTER_ENCODER_H
