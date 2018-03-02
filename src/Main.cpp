/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Entry point into the application
 */

#include "Common.h"
#include "threading/ThreadPool.h"
#include "services/LameService.h"
#include "services/ConsoleLoggingService.h"
#include "services/DirectoryService.h"
#include "Mp3EncoderTask.h"

using namespace std;

LameService lameService;
ConsoleLoggingService loggingService;
DirectoryService directoryService;

/**
 * Prints the date and time
 * @param format The string to print along with the date and time
 */
void printDateTime(const char* format)
{
    string dateTime;

    dateAsString(dateTime);

    loggingService.log(format, dateTime.c_str());
}

/**
 * Application entry point
 * @param argc The number of command line arguments
 * @param args The command line arguments
 * @return The result code
 */
int main(int argc, char* args[])
{
    if (argc < 2)
    {
        loggingService.log("Usage: BulkWavConverter <directory>");
        return 1;
    }

    const char* directory = args[1];

    printDateTime("Task started at %s");

    ThreadPool threadPool(DEFAULT_THREAD_COUNT);

    list<string> files;

    loggingService.log("Reading files from directory '%s'", directory);

    int fileCount = directoryService.getFiles(directory, files);

    if (fileCount > 0)
    {
        loggingService.log("Attempting to encode %d files\n", fileCount);

        for (string& filenameWav : files) {

            string filenameMp3;

            directoryService.getTruncatedPath(filenameWav.c_str(), filenameMp3);
            filenameMp3 += MP3_EXTENSION;

            threadPool.addTask(new Mp3EncoderTask(filenameWav.c_str(), filenameMp3.c_str(), &lameService, &loggingService));
        }

        threadPool.finish();
    }
    else
    {
        loggingService.log(fileCount == -1 ? "Directory does not exist" : "No files found in directory");
    }

    printDateTime("Task completed at %s");

    return 0;
}
