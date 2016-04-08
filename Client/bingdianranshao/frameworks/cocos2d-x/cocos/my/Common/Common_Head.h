#pragma once

#ifndef __COMMON_HEAD_H__
#define __COMMON_HEAD_H__

#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "cocos2d.h"
#include "my/Common/Console_Output.h"

#define NS_GJ           GameJoy
#define US_NS_GJ        using namespace GameJoy
#define NS_GJ_BEGIN     namespace GameJoy {
#define NS_GJ_END       }

#define SERVERIP "10.0.128.158"
#define SERVERPORT 23333

enum
{
    success = 0,
    fail = -1,
    quit = -2,
    error = -3,
};

#define MAX_CSMESSAGE_SIZE 0x3fff

#endif // __COMMON_HEAD_H__
