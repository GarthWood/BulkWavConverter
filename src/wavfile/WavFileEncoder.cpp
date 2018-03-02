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

bool WavFileEncoder::loadAndEncode(const char* path, const char* output, LameService* lameService, string& status)
{
    int headerSize = sizeof(WAV_HEADER);
    bool result = false;

    FILE* wavFile = fopen(path, "rb");

    size_t bytesRead = fread(&header, 1, headerSize, wavFile);

    if (bytesRead == 0)
    {
        status = "File is empty";
    }
    else if (!isWav())
    {
        status = "Not a WAV file";
    }
    else
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

        fclose(wavFile);

        encoder.complete();
        encoder.join();

        result = true;
    }

    return result;
}

bool WavFileEncoder::isWav()
{
    return header.WAVE[0] == 'W' && header.WAVE[1] == 'A' && header.WAVE[2] == 'V' && header.WAVE[3] == 'E';
}