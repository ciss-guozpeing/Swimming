#include "Login.h"
#include "ui_login.h"
#include <QDebug>

#include "mainwindow.h"
#include "src/DB/User.h"

static Login* INSTANCE=nullptr;
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("登录");
    this->setFixedSize(600,400);
    this->setWindowIcon(QIcon(":/images/images/swimming.png"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

Login::~Login()
{
    delete ui;
}

Login* Login::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Login();
    }
    return INSTANCE;
}

bool Login::userType()
{
    return m_userType;
}

void Login::setUserType(bool userType)
{
    m_userType = userType;
}

QString Login::lastLoginUser()
{
    return m_lastLoginUser;
}

void Login::setLastLoginUser(QString lastLoginUser)
{
    m_lastLoginUser = lastLoginUser;
}

void Login::clearPassword()
{
    ui->password->clear();
}


void Login::on_loginButton_clicked()
{
    QString username = ui->username->text();
    QString password = ui->password->text();

    auto user = new DB::User();

    if(user->isSupperUser(username,password)){
        setUserType(true);
    } else{
        setUserType(false);
    }

    if(user->isExistsUser(username,password)){
        accept();
        if(lastLoginUser() != username){
        }
        if(lastLoginUser() == username){

        }
        this->setLastLoginUser(username);
        emit loginOnclicked(username, userType());
        emit showMainWindow();
    } else {
        this->exec();
    }

    user->deleteLater();
}


void Login::on_label_linkActivated(const QString &link)
{
    Q_UNUSED(link);
}


void Login::on_label_linkHovered(const QString &link)
{

    Q_UNUSED(link);
}



