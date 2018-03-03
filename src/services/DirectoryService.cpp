/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * A service to access directory information
 */

#include "DirectoryService.h"

/**
 * Constructor
 */
DirectoryService::DirectoryService()
{
}

/**
 * Destructor
 */
DirectoryService::~DirectoryService()
{
}

/**
 * Gets the list of files in the folder provided and all subfolders
 * @param path The directory
 * @param files THe output file list
 * @param includeSubDirectories Whether to parse subfolders
 * @return The number of files found
 */
int DirectoryService::getFiles(const char* path, list<string>& files, bool includeSubDirectories/* = false*/)
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

            if (isDirectory(fullPath.c_str()))
            {
                if (includeSubDirectories)
                {
                    getFiles(fullPath.c_str(), files);
                }
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

/**
 * Gets the filename less the extension
 * @param path The file path
 * @param filename The output filename
 */
void DirectoryService::getTruncatedPath(const char *path, string &filename)
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

/**
 * Returns whether the specified path is a directory
 * @param path The path
 * @return Whether the specified path is a directory
 */
bool DirectoryService::isDirectory(const char* path)
{
    struct stat statbuf;

    if (stat(path, &statbuf) != 0)
        return false;

    return S_ISDIR(statbuf.st_mode);
}

/****************************************************************************
 * Private Methods
****************************************************************************/

/**
 * Returns whether the specified path must be excluded from the list
 * @param path The path
 * @return Whether the specified path must be excluded from the list
 */
bool DirectoryService::isExcluded(const char* path)
{
    string name(path);

    return name == "." || name == ".." || name == ".DS_Store";
}

/**
 * Appends two paths together
 * @param first The first path
 * @param second The second path
 * @param fullPath The output path
 */
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
