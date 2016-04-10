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
    int ConnectToServer();
	void SetUin(int _uin) { if(uin < 0) uin = _uin; }
private:
    MessageProxy();
    static MessageProxy* instance;
	int uin;
};

}

#endif // !__MESSAGE_PROXY_H__
