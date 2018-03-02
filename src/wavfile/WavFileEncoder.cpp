/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/32128050
 *
 * Loads a WAV file and adds audio chunks to an encoder
 */

#include "WavFileEncoder.h"
#include "Encoder.h"

/**
 * Constructor
 */
WavFileEncoder::WavFileEncoder()
{

}

/**
 * Destructor
 */
WavFileEncoder::~WavFileEncoder()
{

}

/**
 * Loads the WAV file and encodes it at the same time on a separate thread
 * @param path The path to the WAV file
 * @param output The path to the output file
 * @param lameService The gloval LameService
 * @param status The error status in the case of an error
 * @return Whether the file could be encoded
 */
bool WavFileEncoder::loadAndEncode(const char* path, const char* output, LameService* lameService, string& status)
{
    int headerSize = sizeof(WAV_HEADER);
    bool result = false;

    FILE* wavFile = fopen(path, "rb");

    size_t bytesRead = fread(&mHeader, 1, headerSize, wavFile);

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
        Encoder encoder(output, mHeader.SamplesPerSec, mHeader.NumOfChan, lameService);

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


/****************************************************************************
 * Private Methods
****************************************************************************/

/**
 * Whether this file is in WAV format
 * @return Whether this file is in WAV format
 */
bool WavFileEncoder::isWav()
{
    return mHeader.WAVE[0] == 'W' && mHeader.WAVE[1] == 'A' && mHeader.WAVE[2] == 'V' && mHeader.WAVE[3] == 'E';
}
