/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Spawns a new thread and initiates the WAV to MP3 encoding
 */

#ifndef BULKWAVCONVERTER_MP3ENCODERTASK_H
#define BULKWAVCONVERTER_MP3ENCODERTASK_H

#include "Common.h"
#include "threading/ThreadTask.h"
#include "services/LameService.h"
#include "services/ConsoleLoggingService.h"
#include "wavfile/WavFileEncoder.h"
#include "wavfile/Encoder.h"

class Mp3EncoderTask : public ThreadTask
{
public:
    /**
     * Constructor
     * @param inputFilename The audio input source filename
     * @param ouputFilename The output source filename
     * @param lameService The global LameService
     * @param loggingService  The global LoggingService
     */
    Mp3EncoderTask(const char* inputFilename, const char* ouputFilename, LameServicePtr lameService, LoggingServicePtr loggingService);

    /**
     * Destructor
     */
    virtual ~Mp3EncoderTask();

protected:
    /**
     * Executes the encoder task
     */
    virtual void run();

private:

    string mInputFilename;

    string mOutputFilename;

    LameServicePtr mLameService;

    LoggingServicePtr mLoggingService;
};

#endif // BULKWAVCONVERTER_MP3ENCODERTASK_H
