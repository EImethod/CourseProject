#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QtCore>
#include "Client.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<MsgStruct>("MsgStruct"); //ע��Ԫ����,����MsgStruct����Ԫ���ͣ��źźͲ����ӣ�queue�ģ�ʱ�޷��ݴ棡

    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    //QApplication::setFont(QFont("courier new")); //����ȫ������

    //qDebug()<<"main Thread: "<<QThread::currentThreadId()<<endl;

    Client c;

    return a.exec();
}
