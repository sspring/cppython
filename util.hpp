#pragma once

#include <string>
#include <sstream>

namespace util
{
    std::string char2string(char ch)
    {
        std::stringstream stream;
        std::string str;
        stream << ch;
        stream >> str;
        return str;
    }
}

