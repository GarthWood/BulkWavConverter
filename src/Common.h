/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Common vars and methods
 */

#ifndef BULKWAVCONVERTER_COMMON_H
#define BULKWAVCONVERTER_COMMON_H

#include <cstdio>
#include <chrono>
#include <string>

using namespace std;

const int DEFAULT_BUFFER_SIZE = 8196;
const int DEFAULT_THREAD_COUNT = 24;

#define MP3_EXTENSION           ".mp3"

inline long getMilliseconds()
{
    return std::chrono::duration_cast< std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

inline int getFileSize(FILE* file)
{
    fseek(file,0,SEEK_END);

    int size = ftell(file);

    fseek(file,0,SEEK_SET);

    return size;
}

inline void dateAsString(string& output)
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);

    output = buffer;
}

#endif // BULKWAVCONVERTER_COMMON_H
