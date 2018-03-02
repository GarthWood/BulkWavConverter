//
// Created by Garth on 2018/03/01.
//

#ifndef BULKWAVCONVERTER_MP3ENCODERTASK_H
#define BULKWAVCONVERTER_MP3ENCODERTASK_H

#include <lame.h>
#include "threading/ThreadTask.h"
#include "services/LameService.h"
#include "services/LoggingService.h"
#include "wavfile/WavFileEncoder.h"
#include "wavfile/Encoder.h"

using namespace std;

class Mp3EncoderTask : public ThreadTask
{
public:
    Mp3EncoderTask(const char* inputFilename, const char* ouputFilename, LameServicePtr laService, LoggingServicePtr loService);
    virtual ~Mp3EncoderTask();

    virtual void run();

private:

    string _inputFilename;

    string _outputFilename;

    LameServicePtr lameService;

    LoggingServicePtr loggingService;
};


#endif //BULKWAVCONVERTER_MP3ENCODERTASK_H
