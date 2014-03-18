#include"OJServer.h"
#include<QTcpServer>
#include<QTcpSocket>
//#include<QtGui>
#include"MsgStruct.h"
#include<qdebug.h>
#include<time.h>
#include<dir.h>

OJServer::OJServer(QObject *parent)
    : QObject(parent)
{
    QFile conf("configure.txt");
    if( !conf.open(QIODevice::ReadOnly)){
        if( OJ_LOG) qDebug()<<"failed to open configure.txt";
        exit(1);
    }
    judge_home=QString(conf.readLine(100)).trimmed();
    judgeRunID=QString(conf.readLine(100)).toInt();
    if( judge_home[0]=='.' ){
        char dir[1024];
        getcwd(dir,1024);
        judge_home=dir;
    }
    if( OJ_DEBUG ) qDebug()<<"judge_home: "<<judge_home.toStdString().c_str();
    if( OJ_DEBUG ) qDebug()<<"judgeRunID: "<<judgeRunID;

    tcpServer.setMaxPendingConnections(1000);//�������������
    connect(&tcpServer,SIGNAL(newConnection()),this,SLOT(addConnection()));

    //��ʼ�����ݿ�
    db=QSqlDatabase::addDatabase("QODBC","myCon");
    db.setHostName("127.0.0.1");
    QString dsn =
            QString::fromLocal8Bit(
                    "DRIVER={SQL SERVER};SERVER=127.0.0.1;DATABASE=OnlineJudgeDB;uid=OJadmin;pwd=123");
    db.setDatabaseName(dsn);
    db.setUserName("OJadmin");
    db.setPassword("123");

    if( db.open() ){
        if( OJ_LOG ) qDebug()<<"SQL server 2008 has been connected!";
        query=QSqlQuery(db); //����Ǳ����

        if( OJ_DEBUG ){
            query.exec("select * from userinfo");
            while( query.next() ){
                QString s1,s2,s3;
                QVariant v1=query.value(0);

                s1=query.value(0).toString();
                s2=query.value(1).toString();
                s3=query.value(2).toString();

                //qDebug()<<s1<<' '<<s2<<' '<<s3;
            }
        }
    }else{
        if( OJ_LOG ) qDebug()<<db.lastError().text();
        exit(-1);
    }
    readAllProb();
}

void OJServer::readAllProb(){
    query.exec("select * from ProblemSet");
    Problem p;
    while( query.next() ){
        p.probID=query.value(0).toInt();
        p.probName=query.value(1).toString();
        p.probFileAddr=query.value(2).toString();
        p.inputFileAddr=query.value(3).toString();
        p.outputFileAddr=query.value(4).toString();
        p.runTimeLimit=query.value(5).toInt();
        p.runMemoryLimit=query.value(6).toInt();
        p.totalTry=query.value(7).toInt();
        p.totalSolved=query.value(8).toInt();
        probs.push_back(p);
        //if( OJ_DEBUG ) qDebug()<<(p.toString());
    }
    if( OJ_DEBUG ) qDebug()<<"read all problems successfully";
}

void OJServer::startServer(){
    tcpServer.listen(QHostAddress::Any,HOSTPORT);
    if( OJ_DEBUG )
        qDebug()<<"server Address: "<<tcpServer.serverAddress()<<"port: "<<tcpServer.serverPort();
}

void OJServer::addConnection(){
    LinkedUser *tmp=new LinkedUser(0);
    tmp->tcpSocket=tcpServer.nextPendingConnection();
    connect(tmp->tcpSocket,SIGNAL(readyRead()),tmp,SLOT(readMsg()));

    MsgStruct m;
    m.msgType=MSG_TYPE_CONFIRM;  //����ȷ����Ϣ
    tmp->sendMsg(m);

    for(pit=probs.begin();pit!=probs.end();++pit){ //�������е���Ŀ����
        m.msgType=MSG_TYPE_GET_PROB;
        m.msg=(*pit).toString();
        tmp->sendMsg(m);
    }

    connect(tmp,SIGNAL(hadMsg(MsgStruct)),this,SLOT(processMsg(MsgStruct)));
    connect(tmp->tcpSocket,SIGNAL(disconnected()),
            this,SLOT(disConnected())); //����
    linkedUsers.push_back(tmp);  //�Ž�ȥ

    if( OJ_DEBUG ) qDebug()<<"new Connection!  had send confirm msg";
}

void OJServer::processMsg(MsgStruct m){
    LinkedUser *msgSender=(LinkedUser*)sender();

    if( m.msgType == MSG_TYPE_REGISTER ){
        UserInfo user;
        user.initWithQString(m.msg);
        QString cmd=QString("select * from UserInfo where userID='").append(user.userID).append("'");
        if( query.exec(cmd) ){
            MsgStruct msg;
            if( query.next() ){
                msg.msgType=MSG_TYPE_REGISTER_FAIL;
            }else{
                msg.msgType=MSG_TYPE_REGISTER_SUC;
                this->insertUserInfoToDB(user);
            }
            msgSender->sendMsg(msg);
        }else{
            qDebug()<<tr("Query failed! ").append(cmd);
        }
    }else if(m.msgType==MSG_TYPE_LOGIN ){
        UserInfo user;
        user.initWithQString(m.msg);
        QString cmd=QString("select * from UserInfo where userID='").append(user.userID).append("'");
        if( query.exec(cmd) ){
            MsgStruct msg;
            if( query.next() && query.value(1).toString()==user.password ){
                msgSender->userInfo.userID=query.value(0).toString();
                msgSender->userInfo.password=query.value(1).toString();
                msgSender->userInfo.qqNumber=query.value(2).toString();
                msgSender->userInfo.solved=query.value(3).toInt();
                msgSender->userInfo.rating=query.value(4).toInt();
                msgSender->loginSuc=true;
                msg.msgType=MSG_TYPE_LOGIN_SUC;
                msg.msg=msgSender->userInfo.toQString();
            }else{
                msg.msgType=MSG_TYPE_LOGIN_FAIL;
            }
            msgSender->sendMsg(msg);
            if( msg.msgType == MSG_TYPE_LOGIN_SUC ){ //֪ͨ���������û���һ�����û���½��

                msg.msgType=MSG_TYPE_USERLOGIN;
                msg.user=msgSender->userInfo;
                for(QList<LinkedUser*>::Iterator it=linkedUsers.begin();it!=linkedUsers.end();++it){
                    if( (*it)->loginSuc==false ) continue;

                    (*it)->sendMsg(msg);

                    if( (*it)!=msgSender ){
                        MsgStruct _msg;
                        _msg.msgType=MSG_TYPE_USERLOGIN;
                        _msg.user=(*it)->userInfo;
                        msgSender->sendMsg(_msg);
                    }
                }
            }
        }else{
            qDebug()<<tr("Query failed! ").append(cmd);
        }
    }else if( m.msgType == MSG_TYPE_CHAT ){
        m.user=msgSender->userInfo;
        for(QList<LinkedUser*>::Iterator it=linkedUsers.begin();it!=linkedUsers.end();++it){
            if( (*it)->loginSuc==false ) continue;
            (*it)->sendMsg(m);
        }
    }else if( m.msgType == MSG_TYPE_PROB_DES ){
        for(pit=probs.begin();pit!=probs.end();++pit){
            if( (*pit).probID == m.probID ) break;
        }
        FILE *f=fopen((*pit).probFileAddr.toStdString().c_str(),"r");
        if( f!=NULL ){ //
            QTextStream input(f);
            input.setCodec("UTF-8");
            m.msg=input.readAll();
            //if( OJ_DEBUG ) qDebug()<<tr("��Ŀ����:")<<m.msg;
            msgSender->sendMsg(m);
        }else{
            m.msgType=MSG_TYPE_SHOWMSG;
            m.msg=tr("No such problem!");
            msgSender->sendMsg(m);
        }
    }else if( m.msgType == MSG_TYPE_CODE ){
        //if( OJ_DEBUG ) qDebug()<<"had received code"<<m.probID<<m.msg;

        QString path=judge_home+"/submitted_code/"+QString::number(judgeRunID)+".cpp";
        if( OJ_DEBUG ) qDebug()<<"\ncode stored in : "<<path.toStdString().c_str();

        QFile src_code(path);
        if( !src_code.open(QIODevice::WriteOnly) ){
            //...
        }
        src_code.write("/*-----this comment added by system------------------\n");
        src_code.write((QString("user: ")+m.user.userID+"\n").toStdString().c_str());
        src_code.write( (QString("probID: ")+QString::number(m.probID)+"\n").toStdString().c_str());
        src_code.write("-----------------------------------------------------*/\n");
        src_code.write(m.msg.toStdString().c_str());
        src_code.flush();

        //judge process
        for(pit=probs.begin();pit!=probs.end();++pit){
            if( (*pit).probID == m.probID ) break;
        }
        QString CEString;
        clock_t _time=clock();
        int result=coreJudge.judge(&(*pit),judge_home, judgeRunID,CEString);
        if( OJ_DEBUG ) qDebug()<<"judge time: "<<clock()-_time<<" ms";
        judgeRunID++; //

        QFile conf("configure.txt");
        if( !conf.open(QIODevice::WriteOnly) ){
            //...
        }
        conf.write((judge_home+"\r\n").toStdString().c_str());
        conf.write( (QString::number(judgeRunID)+"\r\n").toStdString().c_str());
        conf.flush();


        m.msgType=MSG_TYPE_SHOWMSG;
        switch( result ){
        case JUDGE_RES_AC :
            m.msg="Accepted"; break;
        case JUDGE_RES_WA:
            m.msg="Wrong Answer"; break;
        case JUDGE_RES_CE:
            m.msg=QString("Compile Error:\n")+CEString; break;
        case JUDGE_RES_PE:
            m.msg="Presentation Error"; break;
        case JUDGE_RES_RE:
            m.msg="Runtime Error"; break;
        case JUDGE_RES_TLE:
            m.msg="Time Limit Exceeded"; break;
        case JUDGE_RES_MLE:
            m.msg="Memory Limit Exceeded"; break;
        case JUDGE_RES_OLE:
            m.msg="Output Limit Exceeded"; break;
        case JUDGE_RES_INT_ERR:
            m.msg="Judge Internal Error"; break;
        }
        msgSender->sendMsg(m);
    }else if( m.msgType == MSG_TYPE_USERLOGOFF ){
        UserInfo logoffUser;
        for(uit=linkedUsers.begin();uit!=linkedUsers.end();++uit){
            if((*uit) == msgSender ){ //*it����LinkedUser*
                logoffUser=(*uit)->userInfo;
                //linkedUsers.erase(it);   //���ﲻ��ɾ��
                break;
            }
        }
        (*uit)->loginSuc=false; // ����Ϊδ��¼

        MsgStruct msg;
        msg.msgType=MSG_TYPE_USERLOGOFF;
        msg.user=logoffUser;
        for(uit=linkedUsers.begin();uit!=linkedUsers.end();++uit){
            if((*uit)->loginSuc==false ) continue;
            (*uit)->sendMsg(msg);
        }
        if( OJ_DEBUG ) qDebug()<<tr("QList<LinkedUser*> size: ")<<linkedUsers.size();
        if( OJ_DEBUG ) qDebug()<<logoffUser.userID.append(" loged off!");
    }
}

void OJServer::insertUserInfoToDB(UserInfo user){
    QString cmd=QString("insert into UserInfo values ('")
                .append(user.userID).append("','").append(user.password)
                .append("','").append(user.qqNumber).append("',0,0)");
    if( query.exec(cmd) ){
        qDebug()<<tr("�ɹ�ִ�� ").append(cmd);
    }else{
        qDebug()<<tr("��ѯ����ʧ��! ").append(cmd);
    }
}

void OJServer::disConnected(){
    QTcpSocket *tcpSocket=(QTcpSocket*)sender();
    UserInfo logoffUser;
    bool anLoginUser=false;  //�ǲ���һ����½�˵��û�,��Щ��ע���˻���û�е�½�Ľ���
    for(QList<LinkedUser*>::Iterator it=linkedUsers.begin();it!=linkedUsers.end();++it){
        if((*it)->tcpSocket == tcpSocket ){ //*it����LinkedUser*
            logoffUser=(*it)->userInfo;
            if( (*it)->loginSuc ) anLoginUser=true;
            linkedUsers.erase(it);
            break;
        }
    }
    if( anLoginUser ){
        MsgStruct msg;
        msg.msgType=MSG_TYPE_USERLOGOFF;
        msg.user=logoffUser;
        for(QList<LinkedUser*>::Iterator it=linkedUsers.begin();it!=linkedUsers.end();++it){
            if((*it)->loginSuc==false ) continue;
            (*it)->sendMsg(msg);
        }
    }
    if( OJ_DEBUG ) qDebug()<<tr("QList<LinkedUser*> size: ")<<linkedUsers.size();
    if( OJ_DEBUG ) qDebug()<<logoffUser.userID.append(" disConnected!");
}

OJServer::~OJServer(){
    qDebug()<<"~OJServer called!";

    if( query.isActive() ) query.finish();
    if( db.isOpen()) db.close();
    for(QList<LinkedUser*>::Iterator it=linkedUsers.begin();it!=linkedUsers.end();++it){
        delete *it;
    }
    tcpServer.close();
    QSettings _qset;
    _qset.setValue(tr("JudgeRunID"),judgeRunID);
}
