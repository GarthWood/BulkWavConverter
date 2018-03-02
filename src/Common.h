/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * Common vars and methods
 */

#ifndef BULKWAVCONVERTER_COMMON_H
#define BULKWAVCONVERTER_COMMON_H

#ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#endif

#ifdef _WINDOWS
#include <windows.h>
#include <atomic>
#define _TIMESPEC_DEFINED
#define millis __int64
#else
#include <unistd.h>
#include <zconf.h>
#define millis long
#endif

#include <stdio.h>
#include <cstdio>
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <pthread.h>
#include <queue>
#include <list>
#include <vector>
#include <thread>

#include <sys/stat.h>
#include <dirent.h>

using namespace std;

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;

const int DEFAULT_BUFFER_SIZE = 8196;
const int DEFAULT_THREAD_COUNT = 24;

#define MP3_EXTENSION           ".mp3"

inline millis getMilliseconds()
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
