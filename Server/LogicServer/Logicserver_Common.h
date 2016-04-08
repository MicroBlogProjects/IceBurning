#pragma once
#ifndef __LOGICSERVER_COMMON_H__
#define __LOGICSERVER_COMMON_H__

#include "../Common/Common.h"
#include "../Common/Common_Trace.h"
#include "../Common/Function_Wrap.h"

#include "../../Common/include/Message_i.h"

NS_LS_BEGIN

#define MAXEVENTS 5
#define CONNECT_SERVER_PORT 23333
#define SA struct sockaddr

enum
{
    success = 0,
    error = -1,
    fail = -2,
    quit = -3,
};

NS_LS_END

#endif // !__LOGICSERVER_COMMON_H__
