#include "Common_Tools.h"

int EncodeInt32(char*& str, int32_t value)
{
    int p = 0xff000000, w = 24;
    for (int i = 0; i < 4; ++i)
    {
        byte b = (byte)((value & p) >> w);
        *(str++) = (char)((b & 0xf0) >> 4);
        *(str++) = (char)( b & 0x0f);
        p >>= 8;
        w -= 8;
    }
    return 2 * sizeof(int32_t);
}


int32_t DecodeInt32(char*& str)
{
    int ret = 0;
    for (int i = 0; i < 4; i++)
    {
        ret = (ret << 4) | ((*(str++)) & 0x0f);
        ret = (ret << 4) | ((*(str++)) & 0x0f);
    }
    return ret;
}


