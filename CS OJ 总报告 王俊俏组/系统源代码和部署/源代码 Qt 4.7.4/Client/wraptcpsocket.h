#ifndef WRAPTCPSOCKET_H
#define WRAPTCPSOCKET_H

#include "msgstruct.h"
#include <QTcpSocket>
//���봴����װ��Tcp�࣬��Ȼ���߳��������ʳ���
class WrapTcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit WrapTcpSocket(QObject *parent = 0);

signals:
    void hadMsg(MsgStruct m);
public slots:
    void sendMsg(MsgStruct m);
private slots:
    void readMsg();
private:
    quint16 bufLen;
};

#endif // WRAPTCPSOCKET_H
