#pragma once

#include <stdio.h>
#include <direct.h>
#include <tuple>
#include <vector>
#include <numeric>
#include "builtin.hpp"
#include "string.hpp"
#include "util.hpp"
#ifdef _WIN32
    #include <Windows.h>
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
            return string::strip(path,"\r\t\n \\/");
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
            DWORD attrib = ::GetFileAttributesA(path.c_str());
            return (attrib!=INVALID_FILE_ATTRIBUTES &&
                    attrib & FILE_ATTRIBUTE_DIRECTORY);
        }

        bool isfile(std::string path)
        {
            DWORD attrib = ::GetFileAttributesA(path.c_str());
            return (attrib!=INVALID_FILE_ATTRIBUTES &&
                    attrib & ~FILE_ATTRIBUTE_DIRECTORY);
        }

        bool exists(std::string path)
        {
            DWORD attrib = ::GetFileAttributesA(path.c_str());
            return attrib!=INVALID_FILE_ATTRIBUTES;
        }

        std::string join(std::list<const char*> args)
        {
            return  normpath(string::join(
                                 util::char2string(sep).c_str(),
                                 args.begin(),args.end()));
        }
    }
}
