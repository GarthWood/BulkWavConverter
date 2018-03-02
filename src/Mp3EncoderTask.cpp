/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Spawns a new thread and initiates the WAV to MP3 encoding
 */

#include "Common.h"
#include "Mp3EncoderTask.h"

/**
 * Constructor
 * @param inputFilename The audio input source filename
 * @param ouputFilename The output source filename
 * @param lameService The global LameService
 * @param loggingService  The global LoggingService
 */
Mp3EncoderTask::Mp3EncoderTask(const char* inputFilename, const char* ouputFilename, LameServicePtr lameService, LoggingServicePtr loggingService)
: mInputFilename(inputFilename)
, mOutputFilename(ouputFilename)
, mLameService(lameService)
, mLoggingService(loggingService)
{
}

/**
 * Destructor
 */
Mp3EncoderTask::~Mp3EncoderTask()
{

}


/****************************************************************************
 * Protected Methods
****************************************************************************/

/**
 * Executes the encoder task
 */
void Mp3EncoderTask::run()
{
    WavFileEncoder wavFile;
    string status;

    millis encodingStartTime = getMilliseconds();

    if (wavFile.loadAndEncode(mInputFilename.c_str(), mOutputFilename.c_str(), mLameService, status))
    {
		millis encodingDuration = getMilliseconds() - encodingStartTime;

        mLoggingService->log("%s   Duration=%ldms   [SUCCESS]", mInputFilename.c_str(), encodingDuration);
    }
    else
    {
        mLoggingService->log("%s   [ERROR]   %s", mInputFilename.c_str(), status.c_str());
    }
}

