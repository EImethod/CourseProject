#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H


#include<QThread>
#include"wraptcpsocket.h"
#include<QHostAddress>
struct ClientThread : public QThread{
    Q_OBJECT
public:
    ClientThread(QObject *parent=0);
    ClientThread(QHostAddress addr,quint16 port,QObject *parent=0);

    void run();

    //����һ�������źŵķ���,�൱��һ��������
signals:
    void hadMsg(MsgStruct m);//���ϲ�Ľ��
    //˽���ź�
    void toDownSend(MsgStruct m);

public slots:
    void sendMsg(MsgStruct m);//���ϲ�Ľ��
private slots:
    void fromDownHad(MsgStruct m);

private:
    QHostAddress serverAddr;
    quint16 serverPort;
    WrapTcpSocket *wTcpSocket;
};

#endif // CLIENTTHREAD_H
