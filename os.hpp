#ifndef OS_HPP
#define OS_HPP

#include <stdio.h>
#include <string>
#include <list>
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
        WIN32_FIND_DATAA FindFileData;
        HANDLE hFind = ::FindFirstFileA(dir.c_str(), &FindFileData);
        if(hFind != INVALID_HANDLE_VALUE)
        {
                do {
                    if(! (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
                    {
                        files.push_back(FindFileData.cFileName);
                        printf("%s",FindFileData.cFileName);
                    }
                }while(::FindNextFileA(hFind, &FindFileData));
                ::FindClose(hFind);
        }
        return files;
    }
}


#endif // OS_HPP

