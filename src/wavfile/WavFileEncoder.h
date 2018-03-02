//
// Created by Garth on 2018/03/01.
// Adapted from https://stackoverflow.com/a/32128050
//

#ifndef BULKWAVCONVERTER_WAVREADER_H
#define BULKWAVCONVERTER_WAVREADER_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include "../services/LameService.h"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;

class WavFileEncoder
{
    struct WAV_HEADER
    {
        /* RIFF Chunk Descriptor */
        uint8_t         RIFF[4];        // RIFF Header Magic header
        uint32_t        ChunkSize;      // RIFF Chunk Size
        uint8_t         WAVE[4];        // WAVE Header
        /* "fmt" sub-chunk */
        uint8_t         fmt[4];         // FMT header
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
    WavFileEncoder();
    virtual ~WavFileEncoder();

    bool loadAndEncode(const char* path, const char* output, LameService* lameService, string& status);

    inline int getNumChannels() { return header.NumOfChan; }

    inline int getSampleRate() { return header.SamplesPerSec; }

private:

    bool isWav();

private:

    WAV_HEADER header;
};


#endif //BULKWAVCONVERTER_WAVREADER_H
