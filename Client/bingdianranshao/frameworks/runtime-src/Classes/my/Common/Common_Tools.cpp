#include "Common_Tools.h"

int EncodeInt32(char*& str, int32_t value)
{
    int p = 0xff000000, w = 24;
    for (int i = 0; i < 4; ++i)
    {
        *(str++) = (value & p) >> w;
        p >>= 8;
        w -= 24;
    }
    return success;
}


int32_t DecodeInt32(char*& str)
{
    int ret = 0;
    for (int i = 0; i < 4; i++)
    {
        ret = (ret << 8) | *(str++);
    }
    return ret;
}


