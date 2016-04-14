#pragma once
#ifndef __CSYNC_FRAME_H__
#define __CSYNC_FRAME_H__

#include "../Logicserver_Common.h"
#include "Logicserver_FrameBase.h"
#include "../../Proto_out/GamePlay.h"

NS_LS_BEGIN

class CSyncFrame : public CFrameBase
{
public:
    static CSyncFrame* Instance();
    virtual int32_t ProcessRequest(const CMessage& message);

    int32_t OnNewRoomStartFight(int32_t roomID);
    int32_t OnRoomFinishedFight(int32_t roomID);
    void OnOneFrameFinished();
private:
    CSyncFrame();
    int32_t ProcessRequestRecvOneStep(const CMessage& message);
    void ClearSyncFrames(std::vector<const PBFrameMessage*>& room);
private:
    static CSyncFrame* instance;
    std::map<int32_t, std::vector<const PBFrameMessage*> > sync_frames_;
};

NS_LS_END

#endif // !__CSYNC_FRAME_H__
