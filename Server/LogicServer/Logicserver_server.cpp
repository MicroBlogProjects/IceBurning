#include "Logicserver_Common.h"
#include "Network/Logicserver_EpollUnit.h"
#include "Network/Logicserver_Socket.h"
#include "LogicFrame/Logicserver_LogicFrame.h"
US_NS_LS;

bool Initialize()
{
    EPOLLUNIT->Initialize();

    int32_t logic_fd = LOGICSOCKET->ConnectToConnectserver();
    if (logic_fd == error)
    {
        printf("connect to connect server failed.");
        return false;
    }

    EPOLLUNIT->EpollRegist(logic_fd, LOGICFRAME->HandleMessage);

    return true;
}

void working()
{
    do 
    {
        struct timeval tvNowTime;
        gettimeofday(&tvNowTime, NULL);

        EPOLLUNIT->EpollRun();
        LOGICFRAME->CheckTimer(tvNowTime);
    } while (true);
    
}

int main(int argc, char ** args)
{
    if (!Initialize())
    {
        printf("Initialize program failed");
    }
    working();
    return 0;
}