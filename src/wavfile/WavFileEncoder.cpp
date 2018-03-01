//
// Created by Garth on 2018/03/01.
//

#include "WavFileEncoder.h"
#include "../Common.h"
#include "Encoder.h"

WavFileEncoder::WavFileEncoder()
{

}

WavFileEncoder::~WavFileEncoder()
{

}

int WavFileEncoder::loadAndEncode(const char* path, const char* output, LameService* lameService)
{
    int headerSize = sizeof(WAV_HEADER), filelength = 0;

    FILE* wavFile = fopen(path, "rb");

    if (wavFile == nullptr)
        return 1;

    size_t bytesRead = fread(&header, 1, headerSize, wavFile);

    if (bytesRead > 0)
    {
        int16_t buffer[DEFAULT_BUFFER_SIZE];
        Encoder encoder(output, header.SamplesPerSec, header.NumOfChan, lameService);

        encoder.start();

        while ((bytesRead = fread(buffer, sizeof buffer[0], DEFAULT_BUFFER_SIZE, wavFile)) > 0)
        {
            auto stBuf = new Encoder::stChunk();

            stBuf->buffer = new int16_t[bytesRead];

            memcpy(stBuf->buffer, buffer, (size_t) bytesRead * sizeof(buffer[0]));

            stBuf->size = bytesRead;

            encoder.addChunk(stBuf);
        }

        encoder.complete();

        encoder.join();

        filelength = getFileSize(wavFile);
    }

    fclose(wavFile);

    return filelength;
}
