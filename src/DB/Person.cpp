#include "Person.h"
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
    qDebug() << select_sql;
    if(!select_query.exec()){
        qDebug() << select_query.lastError();
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
            qDebug() << create_query.lastError();
            this->close();
        } else {
            qDebug() << create_query.executedQuery();
        }
    }
}

