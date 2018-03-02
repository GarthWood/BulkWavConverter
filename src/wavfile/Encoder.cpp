//
// Created by Garth on 2018/03/01.
//

#include <zconf.h>
#include "Encoder.h"

Encoder::Encoder(const char* outputFilename, int sampleRate, int numChannels, LameService* lameService)
: _lameService(lameService)
, waiting(true)
, _numChannels(numChannels)
{
    pthread_mutex_init(&mutex, 0);

    _outputFile = fopen(outputFilename, "wb");

    _lame = lameService->createLameInstance(sampleRate, numChannels);
}

Encoder::~Encoder()
{
    if (!_chunks.empty())
    {
        pthread_mutex_lock(&mutex);

        while (!_chunks.empty())
        {
            auto buffer = _chunks.front();
            _chunks.pop();

            delete buffer->buffer;
            delete buffer;
        }
    }

    pthread_mutex_unlock(&mutex);

    if (_outputFile != nullptr)
    {
        fclose(_outputFile);
    }

    _lameService->destroyLameInstance(_lame);

    pthread_mutex_destroy(&mutex);
}

void Encoder::run()
{
    while (waiting || !_chunks.empty())
    {
        if (!_chunks.empty())
        {
            while (!_chunks.empty())
            {
                stChunk* chunk = nullptr;

                pthread_mutex_lock(&mutex);
                chunk = _chunks.front();
                _chunks.pop();
                pthread_mutex_unlock(&mutex);

                if (chunk != nullptr)
                {
                    encode(chunk);
                }
            }
        }
        else {
            usleep(100);
        }
    }

    unsigned char encodedBuffer[DEFAULT_BUFFER_SIZE];
    int bytesWriten = lame_encode_flush(_lame, encodedBuffer, DEFAULT_BUFFER_SIZE);

    fwrite(encodedBuffer, (size_t) bytesWriten, 1, _outputFile);
}

void Encoder::addChunk(stChunk *chunk)
{
    pthread_mutex_lock(&mutex);

    _chunks.push(chunk);

    pthread_mutex_unlock(&mutex);
}

void Encoder::complete()
{
    waiting = false;
}

void Encoder::encode(stChunk* chunk)
{
    int bytesWriten = 0;
    unsigned char encodedBuffer[DEFAULT_BUFFER_SIZE];

    if (_numChannels == 1)
    {
        bytesWriten = lame_encode_buffer(_lame, chunk->buffer, chunk->buffer, chunk->size, encodedBuffer, chunk->size);
    }
    else
    {
        bytesWriten = lame_encode_buffer_interleaved(_lame, chunk->buffer, chunk->size / 2, encodedBuffer, DEFAULT_BUFFER_SIZE);
    }

    fwrite(encodedBuffer, (size_t) bytesWriten, 1, _outputFile);

    delete chunk->buffer;
    delete chunk;
}