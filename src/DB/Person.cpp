﻿#include "Person.h"
#include "src/Common/Log.h"
using namespace DB;
Person::Person(): Base()
{

}
bool Person::_isExistsPerson(QString name, QString birthday, QString gender)
{
    this->open();
    QSqlQuery select_query;
    QString select_sql = QString("SELECT COUNT(name) from person where name='%1' AND birthday='%2' AND gender='%3'").arg(name,birthday,gender);
    select_query.prepare(select_sql);
    if(!select_query.exec()){
        QString text = select_query.lastError().text();
        LOG_ERROR(text);
        this->close();
        return false;
    } else {
        select_query.next();
        if(select_query.value(0).toInt()){
            this->close();
            return true;
        } else{
            this->close();
            return false;
        }
    }
}

void Person::createPerson(QString name, QString birthday, QString gender, QString weight)
{
    bool isExists = this->_isExistsPerson(name,birthday,gender);
    if(!isExists){
        this->open();
        QSqlQuery create_query;
        QString create_sql = QString("insert into person(name,birthday,gender,weight) VALUES('%1','%2','%3','%4')").arg(name,birthday,gender,weight);
        create_query.prepare(create_sql);
        if(!create_query.exec()){
            QString text = create_query.lastError().text();
            LOG_ERROR(text);
            this->close();
        } else {
            QString text = create_query.executedQuery();
            LOG_INFO(text);
        }
    }
}

void Person::updatePerson(QString name, QString gender, QString birthday, QString weight)
{
    auto logger = Log::instance();
    QString title ="更新记录人员";
    bool isExistsPerson = this->_isExistsPerson(name, birthday, gender);
    if(isExistsPerson){
        this->open();
        QSqlQuery update_query;
        QString update_sql = QString("update person set weight='%1' where name='%2' and gender='%3' and birthday='%4'").arg(weight,name,gender,weight);
        update_query.prepare(update_sql);
        if(!update_query.exec()){
            QString text = "更新记录人员数据库执行错误";
            LOG_ERROR(title+"-"+ text);
            logger->sendNotify(logger->LOGGERTYPE::ERROR,title,text);
        } else {
            LOG_INFO("更新记录人员");
        }
    }
}

