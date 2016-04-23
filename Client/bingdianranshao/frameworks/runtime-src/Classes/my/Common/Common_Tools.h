#pragma once
#ifndef __COMMON_TOOLS_H__
#define __COMMON_TOOLS_H__

#include "my/Common/Common_Head.h"

int EncodeInt32(char*& str, int32_t value);
int32_t DecodeInt32(char*& str);

#endif // !__COMMON_TOOLS_H__