#ifndef STRING_HPP
#define STRING_HPP

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
}

#endif
