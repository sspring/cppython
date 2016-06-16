#ifndef OS_HPP
#define OS_HPP

#include <stdio.h>
#include <string>
#ifdef _WIN32
    #include <direct.h>
#else
    #include <unistd.h>
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
}


#endif // OS_HPP

