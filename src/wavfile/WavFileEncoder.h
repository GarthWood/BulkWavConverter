/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Adapted from https://stackoverflow.com/a/32128050
 *
 * Loads a WAV file and adds audio chunks to an encoder
 */

#ifndef BULKWAVCONVERTER_WAVREADER_H
#define BULKWAVCONVERTER_WAVREADER_H

#include "../Common.h"
#include "../services/LameService.h"

class WavFileEncoder
{
    /**
     * WAVE file header
     */
    struct WAV_HEADER
    {
        /* RIFF Chunk Descriptor */
        uint8_t         RIFF[4];        // RIFF Header Magic mHeader
        uint32_t        ChunkSize;      // RIFF Chunk Size
        uint8_t         WAVE[4];        // WAVE Header
        /* "fmt" sub-chunk */
        uint8_t         fmt[4];         // FMT mHeader
        uint32_t        Subchunk1Size;  // Size of the fmt chunk
        uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
        uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
        uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
        uint32_t        bytesPerSec;    // bytes per second
        uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
        uint16_t        bitsPerSample;  // Number of bits per sample
        /* "data" sub-chunk */
        uint8_t         Subchunk2ID[4]; // "data"  string
        uint32_t        Subchunk2Size;  // Sampled data length
    };

public:
    /**
     * Constructor
     */
    WavFileEncoder();

    /**
     * Destructor
     */
    virtual ~WavFileEncoder();

    /**
     * Loads the WAV file and encodes it at the same time on a separate thread
     * @param path The path to the WAV file
     * @param output The path to the output file
     * @param lameService The gloval LameService
     * @param status The error status in the case of an error
     * @return Whether the file could be encoded
     */
    bool loadAndEncode(const char* path, const char* output, LameService* lameService, string& status);

    /**
     * Retrieves the number of channels
     * @return The number of channels
     */
    inline int getNumChannels() { return mHeader.NumOfChan; }

    /**
     * Retrieves the sample rate
     * @return The sameple rate
     */
    inline int getSampleRate() { return mHeader.SamplesPerSec; }

private:

    /**
     * Whether this file is in WAV format
     * @return Whether this file is in WAV format
     */
    bool isWav();

private:

    WAV_HEADER mHeader;
};

#endif // BULKWAVCONVERTER_WAVREADER_H
