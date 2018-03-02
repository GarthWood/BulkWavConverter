/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Spawns a thread to encode audio data
 */

#ifndef BULKWAVCONVERTER_ENCODER_H
#define BULKWAVCONVERTER_ENCODER_H

#include "../Common.h"
#include "../threading/Thread.h"
#include "../services/LameService.h"
#include "WavFileEncoder.h"

class Encoder : public Thread
{
public:

    /**
     * A chunk of audio data
     */
    struct stChunk
    {
        int16_t* buffer;
        int size;
    };

public:
    /**
     * Constructor
     * @param outputFilename The audio output filename
     * @param sampleRate The input sample rate
     * @param numChannels The number of channels in the input audio
     * @param lameService The global LameService
     */
    Encoder(const char* outputFilename, int sampleRate, int numChannels, LameService* lameService);

    /**
     * Destructor
     */
    virtual ~Encoder();

    /**
     * Executes the encoding task
     */
    virtual void run();

    /**
     * Adds a new audio chunk to encode
     * @param chunk The chunk to encode
     */
    void addChunk(stChunk *chunk);

    /**
     * Informs the encoder that all data has been added
     */
    void complete() { mWaiting = false; }

private:

    /**
     * Encodes the audio chunk
     * @param chunk The audio chunk
     */
    void encode(stChunk* chunk);

private:

    FILE* mOutputFile;

    queue<stChunk*> mChunks;

    lame_t mLame;

    LameService* mLameService;

    volatile atomic_bool mWaiting;

    pthread_mutex_t mMutex;

    int mNumChannels;
};

#endif // BULKWAVCONVERTER_ENCODER_H
