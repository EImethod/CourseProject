#ifndef LINKEDUSER_H
#define LINKEDUSER_H

#include <QObject>
#include "UserInfo.h"
#include <QTcpSocket>
#include "MsgStruct.h"

class LinkedUser : public QObject
{
    Q_OBJECT
public:
    UserInfo userInfo;
    bool loginSuc; //�Ƿ����Ѿ��ɹ���½��

    QTcpSocket *tcpSocket;
    quint16 bufLen;

    explicit LinkedUser(QObject *parent = 0);
    void sendMsg(MsgStruct m);
    ~LinkedUser();

private slots:
    void readMsg();
signals:
    void hadMsg(MsgStruct msg);
};

#endif // LINKEDUSER_H
