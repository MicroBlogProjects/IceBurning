#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__

#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>


#include <time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#define NS_GJ           GameJoy
#define US_NS_GJ        using namespace GameJoy
#define NS_GJ_BEGIN     namespace GameJoy {
#define NS_GJ_END       }

#define NS_LG           NS_GJ::LOG
#define US_NS_LG        using namespace LOG
#define NS_LG_BEGIN     namespace GameJoy { namespace LOG {
#define NS_LG_END       } }

#define NS_CS           NS_GJ::ConnectServer
#define US_NS_CS        using namespace ConnectServer
#define NS_CS_BEGIN     namespace GameJoy { namespace ConnectServer {
#define NS_CS_END       } }

#define NS_LS           NS_GJ::LogicServer
#define US_NS_LS        using namespace LogicServer
#define NS_LS_BEGIN     namespace GameJoy { namespace LogicServer {
#define NS_LS_END       } }


#endif // !__COMMON_H__
