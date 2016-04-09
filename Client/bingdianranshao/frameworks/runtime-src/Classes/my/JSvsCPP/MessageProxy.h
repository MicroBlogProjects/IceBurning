#pragma once
#ifndef __MESSAGE_PROXY_H__
#define __MESSAGE_PROXY_H__

namespace GameJoy {

class MessageProxy
{
public:
    static MessageProxy* Instance();
    void SendRequest(int msgID);
    int RecvResponse();
private:
    MessageProxy() {}
    static MessageProxy* instance;
};

}

#endif // !__MESSAGE_PROXY_H__
