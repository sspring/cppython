#pragma once

#include <stdio.h>
#include <string>
#include <list>
#include "os/path.hpp"
#ifdef _WIN32
    #include <direct.h>
    #include <windows.h>
#else
    #include <unistd.h>
    #define MAX_PATH 260
#endif

namespace os
{
    std::string getcwd()
    {
        char buffer[255];
        _getcwd(buffer,255);
        return std::string(buffer);
    }

    void chdir(const std::string path)
    {
        _chdir(path.c_str());
    }

    std::list<std::string>
    listdir(std::string dir)
    {
        std::list<std::string> files;
#ifdef _WIN32
        WIN32_FIND_DATAA FindFileData;
        dir = os::path::normpath(dir+"/*.*");
        HANDLE hFind = ::FindFirstFileA(dir.c_str(), &FindFileData);
        if(hFind != INVALID_HANDLE_VALUE)
        {
                do {
                    if(strcmp(".",FindFileData.cFileName) &&
                            strcmp("..",FindFileData.cFileName))
                    {
                        files.push_back(FindFileData.cFileName);
                    }
                }while(::FindNextFileA(hFind, &FindFileData));
                ::FindClose(hFind);
        }
#endif
        return files;
    }
}

