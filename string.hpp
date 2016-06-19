#pragma once

#include <string>

namespace string
{
    std::string lstrip(std::string str,std::string chars="\r\n\t ")
    {
        if(chars.length()!=0)
        {
            while(str.length()!=0 &&
                  chars.find(str[0])!=std::string::npos)
            {
                str = str.substr(1);
            }
        }
        return str;
    }

    std::string rstrip(std::string str,std::string chars="\r\n\t ")
    {
        if(chars.length()!=0)
        {
            while(str.length()!=0 &&
                  chars.find(str.back())!=std::string::npos)
            {
                str.pop_back();
            }
        }
        return str;
    }

    std::string strip(std::string str,std::string chars="\r\n\t ")
    {
        return rstrip(lstrip(str,chars),chars);
    }

    template<typename Iter_Begin,typename Iter_End>
    std::string join(const char* sep,Iter_Begin begin,Iter_End end)
    {
        std::string result;
        if(begin!=end)
        {
            result = *(begin++);
            for(;begin!=end;++begin)
            {
                result.append(sep).append(*begin);
            }
        }
        return  result;
    }
}
