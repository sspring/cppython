#pragma once

#include <stdio.h>
#include <tuple>
#include <vector>
#include <numeric>
#include "builtin.hpp"
#include "string.hpp"
#include "util.hpp"
#ifdef _WIN32
    #include <Windows.h>
    #include <direct.h>
#else
    #include <sys/stat.h>
    #include <unistd.h>
#endif

namespace os
{
    namespace path
    {

        #ifdef _WIN32
            const char sep='\\';
        #else
            const char sep='/';
        #endif

        std::string normpath(std::string path)
        {
            for(int i=0;i<path.length();++i)
            {
                if(path[i]!=sep &&
                        (path[i]=='\\' ||
                        path[i]=='/'))
                {
                    path[i] = sep;
                    --i;
                }
                else if(path[i] == sep &&
                        i+1 <path.length())
                {
                    if(path[i+1]=='/'|| path[i+1]=='\\')
                    {
                        path.erase(i+1,1);
                        --i;
                    }
                }
            }
#ifdef _WIN32
            return string::strip(path,"\r\t\n \\/");
#else
            return string::strip(path,"\r\t\b \\");
#endif
        }

        std::tuple<std::string,std::string>
        split(std::string path)
        {
            size_t last = path.length()-1;
            while(last>=0)
            {
                if(path[last]=='/' ||
                        path[last]=='\\')
                {
                    break;
                }
                --last;
            }
            return std::tuple<std::string,std::string>
                    (string::rstrip(path.substr(0,last),"\r\t\n \\/"),
                     string::lstrip(path.substr(last),"\r\t\n \\/"));
        }

        std::tuple<std::string,std::string>
        splitext(std::string path)
        {
            size_t last = path.find_last_of('.');
            last = (last==-1)?path.length():last;
            return std::tuple<std::string,std::string>
                    (path.substr(0,last),path.substr(last));
        }

        bool isdir(std::string path)
        {
#ifdef _WIN32
            DWORD attrib = ::GetFileAttributesA(path.c_str());
            return (attrib!=INVALID_FILE_ATTRIBUTES &&
                    attrib & FILE_ATTRIBUTE_DIRECTORY);
#else
            struct stat s;
            return  stat(path.c_str(),&s) == 0 && s.st_mode & S_IFDIR;
#endif
        }

        bool isfile(std::string path)
        {
#ifdef _WIN32
            DWORD attrib = ::GetFileAttributesA(path.c_str());
            return (attrib!=INVALID_FILE_ATTRIBUTES &&
                    attrib & ~FILE_ATTRIBUTE_DIRECTORY);
#else
            struct stat s;
            return  stat(path.c_str(),&s) == 0 && !(s.st_mode & S_IFDIR);
#endif
        }

        bool exists(std::string path)
        {
#ifdef _WIN32
            DWORD attrib = ::GetFileAttributesA(path.c_str());
            return attrib!=INVALID_FILE_ATTRIBUTES;
#else
            struct stat s;
            return  stat(path.c_str(),&s) == 0;
#endif
        }

        std::string join(std::list<const char*> args)
        {
            return  normpath(string::join(
                                 util::char2string(sep).c_str(),
                                 args.begin(),args.end()));
        }
    }
}
