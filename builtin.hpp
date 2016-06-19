#pragma once

#include <vector>
#include <string>
#include <list>

template<typename T>
std::list<T> l(T arg)
{
    std::list<T> retValue;
    retValue.push_back(arg);
    return retValue;
}

template<typename T, typename... Args>
std::list<T> l(T value, Args... args)
{
    std::list<T> retValue;
    retValue.push_back(value);
    for (T arg : l(args...))
    {
        retValue.push_back(arg);
    }
    return retValue;
}
