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
{
}

Mp3EncoderTask::~Mp3EncoderTask()
{

}

void Mp3EncoderTask::run()
{
    WavFileEncoder wavFile;
    string status;

    long encodingStartTime = getMilliseconds();

    if (wavFile.loadAndEncode(_inputFilename.c_str(), _outputFilename.c_str(), lameService, status))
    {
        long encodingDuration = getMilliseconds() - encodingStartTime;

        loggingService->log("%s   Duration=%ldms   [SUCCESS]", _inputFilename.c_str(), encodingDuration);
    }
    else
    {
        loggingService->log("%s   [ERROR]   %s", _inputFilename.c_str(), status.c_str());
    }
}

