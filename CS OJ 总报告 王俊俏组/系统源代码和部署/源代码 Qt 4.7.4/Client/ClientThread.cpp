#include "ClientThread.h"
#include<QtCore>
#include<QtGui>
#include<QHostAddress>
#include"MsgStruct.h"
#include"wraptcpsocket.h"
ClientThread::ClientThread(QObject *parent)
    : QThread(parent)
{
}

ClientThread::ClientThread(QHostAddress addr, quint16 port,QObject *parent)
    : QThread(parent)
{
    this->serverAddr=addr;
    this->serverPort=port;

    qDebug()<<"ClientThread constructor: "<<QThread::currentThreadId()<<endl;
}
/*
���˲飬ԭ��Ӧ���ǣ���QThread�ж�������ж��������ڴ�����QThread���̡߳�
�����ڹ��캯���г�ʼ����mTcpClientӦ�������ڸ��̵߳ģ���ô��run�е���ʱ�����ڿ��̵߳��á�
���԰�mTcpClient�ŵ�run�г�ʼ���������̵߳��ˣ�����ʱ�Ͳ�����ֿ��̵߳��õ����⡣
  */
/*
 zjut_DD���߳����ź�-�ۻ��Ƶ���⣺
 ���ȣ�һ���������Ǹ��߳��д�������ô������Դ�������ģ������������Ǹ��̵߳ģ�
 �����ź�-����һ���������ӵ�����һ������Ļ��ƣ���ô�������������Դ���ڲ�ͬ����ʱ��Qt::AutoConnection ����Qt::QueueConnection
 �������ͬһ���߳��еģ���ô����Qt::DirectConnection

 �����������߳���ʱ���ǿ���ǿ��DirectConnection�ģ������Ϳ��Ի����߳���ִ���ˣ�

 �������Ǳ���   ���̵߳�����Դ��������   �Ĺؼ�
 */

void ClientThread::run(){
    qDebug()<<"clientThread run :"<<QThread::currentThreadId()<<endl;

    if( this->serverAddr.isNull() ){
        QMessageBox::about(NULL,tr("error occur!"),tr("no host ip address!"));
        return;
    }
    wTcpSocket=new WrapTcpSocket;

    connect(wTcpSocket,SIGNAL(hadMsg(MsgStruct)),this,SLOT(fromDownHad(MsgStruct)),Qt::QueuedConnection);
    connect(this,SIGNAL(toDownSend(MsgStruct)),wTcpSocket,SLOT(sendMsg(MsgStruct)),Qt::QueuedConnection);

    wTcpSocket->connectToHost(serverAddr,serverPort);
    qDebug()<<"connect to host success!\n";
    exec(); //�����¼�ѭ��
    qDebug()<<"got out of event loop!"<<endl;
}
void ClientThread::sendMsg(MsgStruct m){
    emit toDownSend(m);
}
void ClientThread::fromDownHad(MsgStruct m){
    emit hadMsg(m);
}
/*
void ClientThread::readContent(){
    qDebug()<<"clientThread readContent :"<<QThread::currentThreadId()<<endl;
    QDataStream in(tcpSocket);
    if( len==0 ){
        if( tcpSocket->bytesAvailable()>=sizeof(quint16)){
            in>>len;
        }else{
            return;
        }
    }
    if( tcpSocket->bytesAvailable()<len ){
        return;
    }
    QString msg;
    in>>msg;
    len=0;

    qDebug()<<msg<<"\n";

    tcpSocket->write("I love you!");
    qDebug()<<"had send I love you"<<endl;
}

void ClientThread::sendMessage(QString msg){
//    QByteArray cont;
//    QDataStream out(&cont,QIODevice::WriteOnly);
//    MsgStruct m;
//    m.msgType=MsgStruct::chat;
//    m.content=msg;
//    quint16 len=0;
//    out<<len<<m;
//    out.device()->seek(0);
//    out<<quint16(out.device()->bytesAvailable() - sizeof(quint16));

//    tcpSocket->write(cont);
//    tcpSocket->close();

    qDebug()<<"clientThread sendMessage: "<<QThread::currentThreadId()<<endl;

    qDebug()<<"ready to send a msg \n";
    QByteArray cont;
    QDataStream out(&cont,QIODevice::WriteOnly);

    out<<quint16(0)<<QString("I love you!");
    out.device()->seek(0);
    out<<quint16(cont.size() - sizeof(quint16));


    tcpSocket->write(cont);
    qDebug()<<"had send a msg \n";
    this->quit();
}
*/
