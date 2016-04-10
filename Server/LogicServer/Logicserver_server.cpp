#include "Logicserver_Common.h"
#include "Network/Logicserver_EpollUnit.h"
#include "Network/Logicserver_Socket.h"
#include "LogicFrame/Logicserver_LogicFrame.h"
US_NS_LS;


void working()
{
    EpollUnit* epollUnit = EpollUnit::Instance();
    epollUnit->Initialize();

    int32_t logic_fd = LOGICSOCKET->ConnectToConnectserver();
    if (logic_fd == error)
    {
        printf("connect to connect server failed.");
        return;
    }

    epollUnit->EpollRegist(logic_fd, LOGICFRAME->HandleMessage);

    epollUnit->EpollRun();
}

int main(int argc, char ** args)
{
    working();
    return 0;
}