#include "RegDialog.h"
#include "ui_RegDialog.h"
#include <QtGui>
#include "ConstData.h"
#include "UserInfo.h"

RegDialog::RegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("�û�ע��"));
}

RegDialog::~RegDialog()
{
    delete ui;
}

bool RegDialog::check(UserInfo *userInfo){
    QString userName=ui->userNameEdit->text();
    QString password=ui->passwordEdit->text();
    QString cPassword=ui->confPasswordEdit->text();
    QString qqNumber=ui->qqNumberEdit->text();
    if( userName.length()==0 ||
        password.length()==0 ||
        cPassword.length()==0 ||
        qqNumber.length()==0 ){
        QMessageBox::critical(0,tr("��д����"),tr("�뽫��Ϣ��д����!"));
        return false;
    }
    for(int i=0;i<userName.length();i++){
        if( userName[i]>='a' && userName[i]<='z' ) continue;
        if( userName[i]>='A' && userName[i]<='Z' ) continue;
        if( userName[i]>='0' && userName[i]<='9' ) continue;
        if( userName[i]=='_' ) continue;
        QMessageBox::critical(0,tr("��д����"),tr("�û���ֻ�ܰ�����ĸ,���ֺ��»���!"));
        return false;
    }

    if( userName.length() > MAX_USER_NAME_LEN ){
        QMessageBox::critical(0,tr("��д����"),tr("�û���̫��,��Ҫ����15�ֽ�!"));
        return false;
    }

    if( password != cPassword ){
        QMessageBox::critical(0,tr("��д����"),tr("ǰ�������������벻һ��!"));
        return false;
    }

    if(password.length() > MAX_PASSWORD_LEN ){
        QMessageBox::critical(0,tr("��д����"),tr("���볤��̫��,��Ҫ����15�ֽ�!"));
        return false;
    }

    for(int i=0;i<qqNumber.length();i++){
        if( qqNumber[i]>='0' && qqNumber[i]<='9' ) continue;
        QMessageBox::critical(0,tr("��д����"),tr("����д��ȷ��qq��!"));
        return false;
    }

    if( qqNumber.length() < 5 ){
        QMessageBox::critical(0,tr("��д����"),tr("����д��ȷ��qq��!"));
        return false;
    }
    userInfo->userID=userName;
    userInfo->password=password;
    userInfo->qqNumber=qqNumber;
    return true;
}
