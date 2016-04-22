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
    CPlayer() : uin(-1), roomID(-1) {}
    CPlayer(int32_t _uin) : uin(_uin), roomID(-1) {}
    CPlayer(int32_t _uin, std::string _username): 
        uin(_uin), username(_username), roomID(-1) {}
    CPlayer(int32_t _uin, std::string _username, std::string _password): 
        uin(_uin), username(_username), password(_password), roomID(-1) {}

    int32_t SendMessageToSelf(int32_t msgID, const CMessageBody& body) const;

    int32_t GetUin() const { return uin; }
    void SetUin(int32_t _uin) { uin = _uin; }
    std::string GetUsername() const { return username; }
    void SetUsername(std::string _username) { username = _username; }
    std::string GetPassword() const { return password; }
    void SetPassword(std::string _password) { password = _password; }
    int32_t GetRoomID() const { return roomID; }
    void SetRoomID(int32_t _roomID) { roomID = _roomID; }

private:
    int32_t uin;
    std::string username;
    std::string password;
    int32_t roomID;
};

NS_LS_END

#endif // !__LOGICSERVER_PLAYER_H__