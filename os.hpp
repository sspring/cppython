#pragma once

#include <stdio.h>
#include "stdlib.h"
#include <string>
#include <list>
#include <map>
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
    std::map<std::string,std::string>
    getenv()
    {
        // enum all environment variables
        // use getenv and putenv function if u want get/set one env
        std::map<std::string,std::string> envs;
        for(char **current = environ; *current; current++)
        {
                std::string env(*current);
                size_t index = env.find_first_of("=");
                if(index != env.npos) // no = found
                {
                    envs[env.substr(0,index)] = env.substr(index+1);
                }
        }
        return envs;
    }

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
    listdir(std::string dir,DWORD includeAttrib=0,DWORD excludeAttrib=0)
    {
        // all files and directories if attrib is 0
        std::list<std::string> files;
#ifdef _WIN32
        WIN32_FIND_DATAA FindFileData;
        dir = os::path::normpath(dir);
        HANDLE hFind = ::FindFirstFileA((dir+"/*").c_str(), &FindFileData);
        if(hFind != INVALID_HANDLE_VALUE)
        {
                do {
                    if(strcmp(".",FindFileData.cFileName) &&
                       strcmp("..",FindFileData.cFileName) &&
                       (!includeAttrib || includeAttrib == (FindFileData.dwFileAttributes&includeAttrib))&&
                       (!excludeAttrib || 0 == (FindFileData.dwFileAttributes&excludeAttrib)))
                    {
                        files.push_back(os::path::join(l(dir.c_str(),FindFileData.cFileName)));
                    }
                }while(::FindNextFileA(hFind, &FindFileData));
                ::FindClose(hFind);
        }
#endif
        return files;
    }

    std::list<std::string>
    walk(std::string dir)
    {
        std::list<std::string> files;  // return value
        for(std::string file:listdir(dir))
        {
            if(os::path::isdir(file))
            {
                for(std::string f:walk(file))
                {
                    files.push_back(f); // append stringlist
                }
            }
            else
            {
                files.push_back(file);
            }
        }
        return files;
    }
}

