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
    static int GetUin() { return uin; }
private:
    MessageProxy();
    static MessageProxy* instance;
	static int uin;
        int has_connect_success;
};

}

#endif // !__MESSAGE_PROXY_H__
