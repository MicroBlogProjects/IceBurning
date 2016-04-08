#include "MessageRegister.h"

/*==========================���Ҫע���PB��ͷ�ļ���ע��===========================*/
#include "../Proto_out/Test.h"
RegistPBToMessageID(1, PBTest)
/*==============================================================================*/

NS_LS_BEGIN

MsgRegister* MsgRegister::instance = NULL;

MsgRegister* MsgRegister::Instance()
{
    if (instance == NULL)
    {
        instance = new MsgRegister();
    }
    return instance;
}

void MsgRegister::RegistPBToMsgID(int32_t msgID, CMessageBody* (*func)())
{
    msgID_to_constructor[msgID] = func;
}

CMessageBody* MsgRegister::NewMessageBody(int32_t msgID)
{
    if (msgID_to_constructor.find(msgID) == msgID_to_constructor.end())
    {
        return NULL;
    }
    return msgID_to_constructor[msgID]();
}

NS_LS_END