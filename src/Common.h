//
// Created by Garth on 2018/03/01.
//

#ifndef BULKWAVCONVERTER_COMMON_H
#define BULKWAVCONVERTER_COMMON_H

#include <cstdio>
#include <chrono>

const int DEFAULT_BUFFER_SIZE = 8196;
const int DEFAULT_THREAD_COUNT = 24;

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

#endif //BULKWAVCONVERTER_COMMON_H
