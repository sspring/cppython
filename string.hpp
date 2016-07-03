#pragma once

#include <string>
#include <memory>
#ifdef _WIN32
    #include <Windows.h>
#endif

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

    std::wstring decode(UINT inputcs, std::string str)
    {
        std::wstring out;
        if (str.length() != 0)
        {
            int dwUnicodeLen = MultiByteToWideChar(inputcs, 0, str.c_str(), -1, NULL, 0);
            size_t num = dwUnicodeLen*sizeof(wchar_t);
            std::auto_ptr<wchar_t> pwText(new wchar_t[num]());   // init wchar_t array with () syntax
            MultiByteToWideChar(inputcs, 0, str.c_str(), -1, pwText.get(), dwUnicodeLen);
            out = pwText.get();
        }
        return out;
    }

    std::string encode(UINT inputcs, std::wstring wstr)
    {
        std::string out;
        if (wstr.length() != 0)
        {
            int dwMultiByteLen = WideCharToMultiByte(inputcs, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
            std::auto_ptr<char> pwText(new char[dwMultiByteLen]());   // init char array with () syntax
            WideCharToMultiByte(inputcs, 0, wstr.c_str(), -1, pwText.get(), dwMultiByteLen,NULL,NULL);
            out = pwText.get();
        }
        return out;
    }
}
