#pragma once

#include <string>
#include <memory>
#include "iconv.h"
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

    int _convert(const char *from, const char *to,char* save, size_t savelen,const char *src, size_t srclen)
    {
        if(srclen<=0 || srclen<=0) return -1;
        libiconv_t cd = iconv_open(to, from);
        if( (int)cd == -1) return -1;

        const char   *inbuf = src;
        char *outbuf = save;
        size_t outbufsize = savelen;
        size_t  savesize = 0;
        size_t inbufsize = srclen;
        const char* inptr = inbuf;
        size_t      insize = inbufsize;
        char* outptr = outbuf;
        size_t outsize = outbufsize;

        while (insize > 0)
        {
            size_t res = iconv(cd,(const char**)&inptr,&insize,&outptr,&outsize);
            if (outptr != outbuf) // iconv may change the address of inptr and outptr
            {
                int saved_errno = errno;
                int outsize = outptr - outbuf;
                strncpy(save+savesize, outbuf, outsize);
                errno = saved_errno;
            }
            if (res == (size_t)(-1))
            {
                if (errno == EILSEQ)
                {
                    int one = 1;
                    iconvctl(cd,ICONV_SET_DISCARD_ILSEQ,&one);
                }
                else
                {
                    break;
                }
            }
        }
        iconv_close(cd);
        return errno;
    }

    std::string decode(const char* from,std::string str)
    {
        size_t bsize=(str.length()+1)*2;
        std::auto_ptr<char> buffer(new char[bsize]());
        _convert(from,"UCS-2",buffer.get(),bsize,str.c_str(),str.length());
        return std::string(buffer.get());
    }
    std::string encode(const char* to,std::string str)
    {
        size_t bsize=(str.length()+1)*4;
        std::auto_ptr<char> buffer(new char[bsize]());
        _convert("UCS-2",to,buffer.get(),bsize,str.c_str(),str.length());
        return std::string(buffer.get());
    }
}
