# BulkWavConverter
This bulk converter is a cross-platform command line tool that converts all WAV files in a directory, including subfolders.

# Features
* Thread pool for managing system resources
* Parallel file loading and encoding
* Unit testing using GoogleTest (only one test has been added to demonstrate the usage)

# Supported Platforms
* OSX (tested on High Sierra)
* Linux (tested on CentOS)
* Windows (tested on Windows 8)

# Prerequisites
* CMake 3.9+
* Visual Studio (for Windows builds)

# Build
* Install Visual Studio if on Windows
* Install CMake 3.9 or higher

Ensure the necessary build tools are in the system path, then open a terminal, navigate to the repo location and run the following:

```cmake .```

If on OSX or Linux:

```make```

If on Windows, open the VS solution.

# Usage

```BulkWavConverter <directory>```

```BulkWavConverterTest```
