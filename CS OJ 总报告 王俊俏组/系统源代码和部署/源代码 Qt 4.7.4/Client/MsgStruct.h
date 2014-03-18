#ifndef MSGSTRUCT_H
#define MSGSTRUCT_H

#include<QtCore>
#include<QDataStream>
#include<QByteArray>
#include"ConstData.h"
#include"UserInfo.h"

struct MsgStruct{
public:
    //���ݳ�Ա
    int msgType;
    QString msg;
    int probID; //������ύ����ʱ����
    UserInfo user; //������ȡ��Ϣ��Դ

    MsgStruct();

    QByteArray toByteArray();
    void initWithByteArray(QByteArray *byteArray);
    void initWithQIODevice(QIODevice *device);

    friend QDataStream& operator<<(QDataStream& out,const MsgStruct& obj);
    friend QDataStream& operator>>(QDataStream& in ,MsgStruct& obj);
};

#endif // MSGSTRUCT_H
