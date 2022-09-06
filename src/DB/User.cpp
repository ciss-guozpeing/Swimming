#include "User.h"
#include "src/Common/Log.h"
#include "src/Common/ModuleManager.h"
using namespace DB;
User::User(): Base()
{

}

bool User::isExistsUser(QString username, QString password)
{
    open();
    QSqlQuery select_query;
    QString select_sql = QString("SELECT count(username) from user where username='%1' AND password='%2'").arg(username,password);
    select_query.prepare(select_sql);

    if(!select_query.exec()){
        qDebug()<< select_query.lastError();
        close();
        return false;
    } else {
        select_query.next();
        if(select_query.value(0).toInt()){
            return true;
        } else{
            return false;
        }
    }
}

bool User::isSupperUser(QString username, QString password)
{
    open();
    QSqlQuery select_query;
    QString select_sql = QString("SELECT count(username) from user where username='%1' AND password='%2' and isSupper=1").arg(username,password);
    select_query.prepare(select_sql);
    if(!select_query.exec()){
        close();
        return false;
    } else {
        select_query.next();
        if(select_query.value(0).toInt()){
            return true;
        } else{
            return false;
        }
    }
}

void User::createDefaultSupperUser()
{
    this->open();
    QSqlQuery create_query;
    QString create_sql = "INSERT INTO user(username,password,isSupper) VALUES('admin','admin',1)";
    create_query.prepare(create_sql);
    if(!create_query.exec()){
        qDebug()<< "超级用户创建不成功";
        this->close();
    } else {
        qDebug()<< "超级用户创建成功";
        this->close();
    }

}

void User::createSupperUser(QString username, QString password)
{
    auto moduleManager = ModuleManager::getInstance();
    this->open();
    QSqlQuery exists_query(driver());
    QSqlQuery insert_query(driver());
    QString exists_sql = QString("select count from user where username='%1'").arg(username);
    exists_query.prepare(exists_sql);
    if (!exists_query.exec()){
        LOG_ERROR("创建超级用户-查询已存在用户失败");
        moduleManager->zpNotificationManager()->notify("创建超级用户","查询已存在用户失败",":/images/images/failed.png","");
        this->close();
    } else {
        QString insert_sql = QString("insert into user(username,password,isSupper) values('%1','%2',1)").arg(username,password);
        insert_query.prepare(insert_sql);
        if(!insert_query.exec()){
            LOG_ERROR("创建超级用户-创建超级用户失败");
            moduleManager->zpNotificationManager()->notify("创建超级用户","创建超级用户失败",":/images/images/failed.png","");
        } else {
            moduleManager->zpNotificationManager()->notify("创建超级用户","创建超级用户成功",":/images/images/success.png","");
            LOG_INFO(QString("创建超级用户-创建超级用户'%1'成功").arg(username));
        }
    }
}


void User::createUser(QString username, QString password)
{
    auto moduleManager = ModuleManager::getInstance();
    this->open();
    QSqlQuery exists_query(driver());
    QSqlQuery insert_query(driver());
    QString exists_sql = QString("select count(username) from user where username='%1'").arg(username) ;
    exists_query.prepare(exists_sql);
    if(!exists_query.exec()){
        LOG_ERROR("创建用户-查询用户失败");
    } else {
        exists_query.next();
        if(!exists_query.value(0).toInt()){
            QString insert_sql = QString("insert into user(username,password,isSupper) values('%1','%2',0)").arg(username,password);
            insert_query.prepare(insert_sql);
            if(!insert_query.exec()){
                moduleManager->zpNotificationManager()->notify("创建用户","创建用户失败",":/images/images/failed.png","");
                LOG_ERROR("创建用户-创建用户失败");
            } else {
                moduleManager->zpNotificationManager()->notify("创建用户","创建用户成功",":/images/images/success.png","");
                LOG_INFO(QString("创建用户-创建用户'%1'成功").arg(username));
            }
        } else {
            moduleManager->zpNotificationManager()->notify("创建用户","用户已存在",":/images/images/info.png","");
            LOG_INFO("创建用户-用户已存在");
        }
    }
    this->close();
}

void User::updateUser(QString old_username, QString old_password, QString new_username, QString new_password)
{
    this->open();
    QSqlQuery exists_query(driver());
    QSqlQuery update_query(driver());
    QString exists_sql = QString("select count(username) from user where username='%1' and password='%2'").arg(old_username,old_password) ;
    exists_query.prepare(exists_sql);
    if(!exists_query.exec()){
        LOG_ERROR("更新用户-查询用户失败");
    } else {
        if(exists_query.value(0).toInt()){
            QString update_sql = QString("update user set username=''");

        } else {
            LOG_INFO("更新用户-用户不存在");
        }
    }
    this->close();
}
