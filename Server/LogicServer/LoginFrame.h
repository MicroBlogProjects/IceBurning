
#ifndef __LOGIN_FRAME_H__
#define __LOGIN_FRAME_H__

#include "Logicserver_Common.h"
#include "Logicserver_Message.h"

NS_LS_BEGIN

class CLoginFrame
{
public:
    static CLoginFrame* Instance();
    int32_t ProcessRequest(const CMessage& message);

private:
    CLoginFrame() {}
    static CLoginFrame* instance;
};

NS_LS_END

#endif // !__LOGIN_FRAME_H__