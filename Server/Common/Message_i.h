#pragma once

#ifndef __MESSAGE_I_G__
#define __MESSAGE_I_G__

/*

class CMessageHead
{
    int32_t m_iPackageLen;      //������������ĳ��ȣ��������ֶ�
    int32_t m_iUin;             //��û�е�¼ʱ��û��uin����Ҫ���������Ϊ<=0
    int32_t m_iMessageID;       //��Ϣ����
    int32_t m_iMessageSequece;  //��ϢΨһ��ʶ��
}
*/

/***************************message ID end*********************************/

#define MSG_ON_LOGIN                0x0001 // ��¼����
#define MSG_ON_REGIST               0x0002 // ע������


/***************************message ID end*********************************/

#endif // !__MESSAGE_I_G__
