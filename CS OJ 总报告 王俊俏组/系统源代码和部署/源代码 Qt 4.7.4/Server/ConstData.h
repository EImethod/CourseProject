#ifndef CONSTDATA_H
#define CONSTDATA_H

#include <QString>
//tcp��������,��Ϣ����Э��
//ע��,��һ��UserInfo�ṹ����

#define OJ_LOG 1
#define OJ_DEBUG 1

const int MSG_TYPE_REGISTER                      =     1; //ע��
const int MSG_TYPE_REGISTER_FAIL                 =     11; //ע��ʧ��,�û�����ռ��
const int MSG_TYPE_REGISTER_SUC                  =     12; //ע��ɹ�

//��½,��һ��UserInfo�ṹ
const int MSG_TYPE_LOGIN                         =     2; //��½
const int MSG_TYPE_LOGIN_SUC                     =     9; //��½�ɹ�,server => client
const int MSG_TYPE_LOGIN_FAIL                    =     10; //��½ʧ��,�û������������

//����,��һ�������ַ���
const int MSG_TYPE_CHAT                          =     3; //��������
//��ʾ,��һ��Ҫ��ʾ�������ַ���
const int MSG_TYPE_SHOWMSG                       =     4; //��ʾһ���Ի���,�����û�һЩ����
//�ύ����, ���+����
const int MSG_TYPE_CODE                          =     5; //�ύ����
//���û���½, һ��userInfo�ṹ��
const int MSG_TYPE_USERLOGIN                     =     6; //���û���½
//�����û�ע��, һ��userInfo�ṹ��
const int MSG_TYPE_USERLOGOFF                    =     7; //�û�ע��
//�ͻ��˺ͷ�����֮��������ź�,������������߿ͻ����Ƿ��Ѿ��ɹ����ӵ�������
const int MSG_TYPE_CONFIRM                       =     8; //�����ź�

const int MSG_TYPE_GET_PROB                      =     16; //��Ŀ�б���Ϣ
const int MSG_TYPE_PROB_DES                      =     17; //��Ŀ������Ϣ


const int JUDGE_RES_AC                           =     18;
const int JUDGE_RES_WA                           =     19;
const int JUDGE_RES_MLE                          =     20;
const int JUDGE_RES_CE                           =     21;
const int JUDGE_RES_TLE                          =     22;
const int JUDGE_RES_INT_ERR                      =     23; //�ڲ�����
const int JUDGE_RES_PE                           =     24;
const int JUDGE_RES_RE                           =     25;
const int JUDGE_RES_OLE                          =     26;



const int MAX_USER_NAME_LEN                      =     15; //��û�������
const int MAX_PASSWORD_LEN                       =     15; //�����

const quint16 HOSTPORT                           =     8899;
#endif // CONSTDATA_H
