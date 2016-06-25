#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <list>
#include <map>
#include "os/path.hpp"
#ifdef _WIN32
    #include <stdint.h>
    #include <direct.h>
    #include <windows.h>
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
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

    std::list<std::string>
    listdir(std::string dir,uint32_t includeAttrib=0,uint32_t excludeAttrib=0)
    {
        // all files and directories if attrib is 0
        std::list<std::string> files;
#ifdef _WIN32
        dir = os::path::normpath(dir);
        WIN32_FIND_DATAA FindFileData;
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
#else
        DIR *dirptr = opendir(dir.c_str());
        if(dirptr != NULL)
        {
            struct stat s;
            struct dirent *entry=NULL;
            while (entry = readdir(dirptr))
            {
                std::string abspath = os::path::join(l(dir.c_str(),entry->d_name));
                if(strcmp(entry->d_name,".") &&
                        strcmp(entry->d_name,".." ) &&
                        !stat(abspath.c_str(),&s) &&
                        (!includeAttrib || includeAttrib == (s.st_mode&includeAttrib))&&
                        (!excludeAttrib || 0 == (s.st_mode&excludeAttrib)))
                {

                    files.push_back(abspath);
                }
            }
            closedir(dirptr);
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

