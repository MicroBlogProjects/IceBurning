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
#define MSG_ON_PULL_ROOMS           0x0003 // ��ȡ�����б�
#define MSG_ON_CREATE_ROOM          0x0004 // ������������
#define MSG_ON_JOIN_ROOM            0x0005 // ���뷿������
#define MSG_FIGHT_READY             0x0006 // ׼����ս
#define MSG_FRAME_SYNC              0x0007 // ֡ͬ������
#define MSG_BACK_ROOM				0x0008 // ��Ϸ����������



/***************************message ID end*********************************/

#endif // !__MESSAGE_I_G__
