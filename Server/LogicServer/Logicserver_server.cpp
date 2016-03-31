#include "Logicserver_Common.h"
#include "Logicserver_EpollUnit.h"
#include "Logicserver_LogicFrame.h"
#include "Logicserver_Socket.h"
US_NS_LS;


void working()
{
    LogicFrame* logicFrame = LogicFrame::Instance();

    EpollUnit* epollUnit = EpollUnit::Instance();
    epollUnit->Initialize();

    LogicSocket* logicSocket = LogicSocket::Instance();
    int32_t logic_fd = logicSocket->ConnectToConnectserver();
    if (logic_fd == error)
    {
        printf("connect to connect server failed.");
        return;
    }

    epollUnit->EpollRegist(logic_fd, logicFrame->HandleMessage);

    epollUnit->EpollRun();
}

int main(int argc, char ** args)
{
    working();
    return 0;
}