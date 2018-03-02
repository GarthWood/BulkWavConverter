/**
 * Author: Garth Wood
 * Date: 02 March 2018
 *
 * A service to access directory information
 */

#ifndef BULKWAVCONVERTER_DIRECTORYSERVICE_H
#define BULKWAVCONVERTER_DIRECTORYSERVICE_H

#include <string>
#include <list>

using namespace std;

class DirectoryService
{
public:
    /**
     * Constructor
     */
    DirectoryService();

    /**
     * Destructor
     */
    virtual ~DirectoryService();

    /**
     * Gets the list of files in the folder provided and all subfolders
     * @param path The directory
     * @param files THe output file list
     * @return The number of files found
     */
    int getFiles(const char* path, list<string>& files);

    /**
     * Gets the filename less the extension
     * @param path The file path
     * @param filename The output filename
     */
    void getTruncatedPath(const char *path, string &filename);

private:

    /**
     * Returns whether the specified path is a directory
     * @param path The path
     * @return Whether the specified path is a directory
     */
    bool isDirectory(string& path);

    /**
     * Returns whether the specified path must be excluded from the list
     * @param path The path
     * @return Whether the specified path must be excluded from the list
     */
    bool isExcluded(const char* path);

    /**
     * Appends two paths together
     * @param first The first path
     * @param second The second path
     * @param fullPath The output path
     */
    void appendPath(const char* first, const char* second, string& fullPath);
};

#endif // BULKWAVCONVERTER_DIRECTORYSERVICE_H
