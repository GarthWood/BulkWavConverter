//
// Created by Garth on 2018/03/02.
//

#include <sys/stat.h>
#include <vector>
#include "DirectoryService.h"
#include "dirent.h"

DirectoryService::DirectoryService()
{

}

DirectoryService::~DirectoryService()
{

}

int DirectoryService::getFiles(const char* path, list<string>& files)
{
    DIR* directory;
    dirent* dent;
    int fileCount = 0;

    if ((directory = opendir(path)) != nullptr)
    {
        while ((dent = readdir(directory)) != nullptr)
        {
            if (isExcluded(dent->d_name))
                continue;

            string fullPath;

            appendPath(path, dent->d_name, fullPath);

            if (isDirectory(fullPath))
            {
                getFiles(fullPath.c_str(), files);
            }
            else
            {
                files.push_back(fullPath);
            }
        }

        closedir(directory);

        fileCount = (int) files.size();
    }
    else
    {
        fileCount = -1;
    }

    return fileCount;
}

void DirectoryService::getTruncatedName(const char* path, string& filename)
{
    int len = (int) strlen(path);

    while (--len >= 0)
    {
        if (path[len] == '.')
        {
            break;
        }
    }

    for (int i = 0; i < len; ++i)
    {
        filename += path[i];
    }
}

bool DirectoryService::isDirectory(string& path)
{
    struct stat statbuf;

    if (stat(path.c_str(), &statbuf) != 0)
        return false;

    return S_ISDIR(statbuf.st_mode);
}

bool DirectoryService::isExcluded(const char* path)
{
    string name(path);

    return name == "." || name == ".." || name == ".DS_Store";
}

void DirectoryService::appendPath(const char* first, const char* second, string& fullPath)
{
    size_t len = strlen(first);

    fullPath = first;

    if (first[len - 1] != '/')
    {
        fullPath += '/';
    }

    fullPath += second;
}