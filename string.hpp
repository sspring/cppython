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

int convert(const char *from, const char *to,char* save, int savelen,const char *src, int srclen)
{
        iconv_t cd;
        const char   *inbuf = src;
        char *outbuf = save;
        size_t outbufsize = savelen;
        int status = 0;
        size_t  savesize = 0;
        size_t inbufsize = srclen;
        const char* inptr = inbuf;
        size_t      insize = inbufsize;
        char* outptr = outbuf;
        size_t outsize = outbufsize;

        cd = iconv_open(to, from);
        iconv(cd,NULL,NULL,NULL,NULL);
        if (inbufsize == 0) {
            status = -1;
            goto done;
        }
        while (insize > 0)
        {
            size_t res = iconv(cd,(const char**)&inptr,&insize,&outptr,&outsize);
            if (outptr != outbuf) {
                int saved_errno = errno;
                int outsize = outptr - outbuf;
                strncpy(save+savesize, outbuf, outsize);
                errno = saved_errno;
            }
            if (res == (size_t)(-1)) {
                if (errno == EILSEQ) {
                    int one = 1;
                    iconvctl(cd,ICONV_SET_DISCARD_ILSEQ,&one);
                    status = -3;
                } else if (errno == EINVAL) {
                    if (inbufsize == 0) {
                        status = -4;
                        goto done;
                    } else {
                        break;
                    }
                } else if (errno == E2BIG) {
                    status = -5;
                    goto done;
                } else {
                    status = -6;
                    goto done;
                }
            }
        }
        status = strlen(save);
    done:
        iconv_close(cd);
        return status;
    }


}
