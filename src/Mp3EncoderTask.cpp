//
// Created by Garth on 2018/03/01.
//

#include "Common.h"
#include "Mp3EncoderTask.h"

Mp3EncoderTask::Mp3EncoderTask(const char* inputFilename, const char* ouputFilename, LameServicePtr laService, LoggingServicePtr loService)
: _inputFilename(inputFilename)
, _outputFilename(ouputFilename)
, lameService(laService)
, loggingService(loService)
, encodingStartTime(0)
{
}

Mp3EncoderTask::~Mp3EncoderTask()
{

}

void Mp3EncoderTask::run()
{
    WavFileEncoder wavFile;

    encodingStartTime = getMilliseconds();

    wavFile.loadAndEncode(_inputFilename.c_str(), _outputFilename.c_str(), lameService);

    long encodingDuration = getMilliseconds() - encodingStartTime;

    loggingService->log("%s   Channels=%d   Duration=%ldms   [DONE]", _inputFilename.c_str(), wavFile.getNumChannels(), encodingDuration);
}

