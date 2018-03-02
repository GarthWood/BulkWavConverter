//
// Created by Garth on 2018/03/02.
//

#ifndef BULKWAVCONVERTER_DIRECTORYSERVICE_H
#define BULKWAVCONVERTER_DIRECTORYSERVICE_H

#include <string>
#include <list>

using namespace std;

class DirectoryService
{
public:
    DirectoryService();
    virtual ~DirectoryService();

    int getFiles(const char* path, list<string>& files);

private:

    bool isDirectory(string& path);

    bool isExcluded(const char* path);

    void appendPath(const char* first, const char* second, string& fullPath);
};


#endif //BULKWAVCONVERTER_DIRECTORYSERVICE_H
