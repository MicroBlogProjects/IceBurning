#pragma once
#ifndef __LOGICSERVER_PLAYER_H__
#define __LOGICSERVER_PLAYER_H__

#include "../Logicserver_Common.h"
#include "google/protobuf/message.h"
#include "../Network/Logicserver_Message.h"
#include "../Network/Logicserver_Socket.h"

NS_LS_BEGIN

class CPlayer
{
public:
    CPlayer() : uin(-1) {}
    CPlayer(int32_t _uin) : uin(_uin) {}
    CPlayer(int32_t _uin, std::string _username): 
        uin(_uin), username(_username) {}
    CPlayer(int32_t _uin, std::string _username, std::string _password): 
        uin(_uin), username(_username), password(_password) {}

    int32_t SendMessageToSelf(int32_t msgID, CMessageBody* body);

    int32_t GetUin() const { return uin; }
    void SetUin(int32_t _uin) { uin = _uin; }
    std::string GetUsername() const { return username; }
    void SetUsername(std::string _username) { username = _username; }
    std::string GetPassword() const { return password; }
    void SetPassword(std::string _password) { password = _password; }

private:
    int32_t uin;
    std::string username;
    std::string password;
};

NS_LS_END

#endif // !__LOGICSERVER_PLAYER_H__