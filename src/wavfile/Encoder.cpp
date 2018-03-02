/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Spawns a thread to encode audio data
 */

#include "Encoder.h"

/**
 * Constructor
 * @param outputFilename The audio output filename
 * @param sampleRate The input sample rate
 * @param numChannels The number of channels in the input audio
 * @param lameService The global LameService
 */
Encoder::Encoder(const char* outputFilename, int sampleRate, int numChannels, LameService* lameService)
: mLameService(lameService)
, mWaiting(true)
, mNumChannels(numChannels)
{
    pthread_mutex_init(&mMutex, 0);

    mOutputFile = fopen(outputFilename, "wb");

    mLame = lameService->createLameInstance(sampleRate, numChannels);
}

/**
 * Destructor
 */
Encoder::~Encoder()
{
    if (!mChunks.empty())
    {
        pthread_mutex_lock(&mMutex);

        while (!mChunks.empty())
        {
            auto buffer = mChunks.front();
            mChunks.pop();

            delete buffer->buffer;
            delete buffer;
        }
    }

    pthread_mutex_unlock(&mMutex);

    if (mOutputFile != nullptr)
    {
        fclose(mOutputFile);
    }

    mLameService->destroyLameInstance(mLame);

    pthread_mutex_destroy(&mMutex);
}

/**
 * Executes the encoding task
 */
void Encoder::run()
{
    while (mWaiting || !mChunks.empty())
    {
        if (!mChunks.empty())
        {
            while (!mChunks.empty())
            {
                stChunk* chunk = nullptr;

                pthread_mutex_lock(&mMutex);
                chunk = mChunks.front();
                mChunks.pop();
                pthread_mutex_unlock(&mMutex);

                if (chunk != nullptr)
                {
                    encode(chunk);
                }
            }
        }
        else {
			this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    unsigned char encodedBuffer[DEFAULT_BUFFER_SIZE];
    int bytesWriten = lame_encode_flush(mLame, encodedBuffer, DEFAULT_BUFFER_SIZE);

    fwrite(encodedBuffer, (size_t) bytesWriten, 1, mOutputFile);
}

/**
 * Adds a new audio chunk to encode
 * @param chunk The chunk to encode
 */
void Encoder::addChunk(stChunk *chunk)
{
    pthread_mutex_lock(&mMutex);

    mChunks.push(chunk);

    pthread_mutex_unlock(&mMutex);
}


/****************************************************************************
 * Private Methods
****************************************************************************/

/**
 * Encodes the audio chunk
 * @param chunk The audio chunk
 */
void Encoder::encode(stChunk* chunk)
{
    int bytesWriten = 0;
    unsigned char encodedBuffer[DEFAULT_BUFFER_SIZE];

    if (mNumChannels == 1)
    {
        bytesWriten = lame_encode_buffer(mLame, chunk->buffer, chunk->buffer, chunk->size, encodedBuffer, chunk->size);
    }
    else
    {
        bytesWriten = lame_encode_buffer_interleaved(mLame, chunk->buffer, chunk->size / 2, encodedBuffer, DEFAULT_BUFFER_SIZE);
    }

    fwrite(encodedBuffer, (size_t) bytesWriten, 1, mOutputFile);

    delete chunk->buffer;
    delete chunk;
}
