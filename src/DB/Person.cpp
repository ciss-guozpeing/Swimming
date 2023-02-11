#include "Person.h"
#include "src/Common/Log.h"
#include "src/Common/ReturnData.h"
using namespace DB;
Person::Person(): Base()
{

}
bool Person::_isExistsPerson(QString name, QString birthday, QString gender,QString weight)
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

ReturnData Person::createPerson(QString name, QString birthday, QString gender, QString weight)
{
    auto logger = Log::instance();
    ReturnData returnData;
    QMap<QString,QString> data;
    bool isExists = this->_isExistsPerson(name,birthday,gender,weight);
    if(!isExists){
        this->open();
        QSqlQuery create_query;
        QString create_sql = QString("insert into person(name,birthday,gender,weight) VALUES('%1','%2','%3','%4')").arg(name,birthday,gender,weight);
        create_query.prepare(create_sql);
        if(!create_query.exec()){
            QString text = create_query.lastError().text();
            LOG_ERROR(text);
            returnData.code = "400";
            returnData.data = data;
            return returnData;
        }
        returnData = this->isExistsPerson(name,gender,birthday,weight);
        return returnData;
    } else {
        returnData.code = "400";
        data["error"] = "人员已存在";
        returnData.data = data;
        return returnData;
    }
}

void Person::updatePerson(QString name, QString gender, QString birthday, QString weight)
{
    auto logger = Log::instance();
    QString title ="更新记录人员";
    bool isExistsPerson = this->_isExistsPerson(name, birthday, gender, weight);
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

void Person::deletePerson(QString id)
{
    auto logger = Log::instance();
    QString title = "删除记录人员";
    QString delete_sql = QString("delete from person where id='%1'").arg(id);
    QSqlQuery delete_query;
    delete_query.prepare(delete_sql);
    if(!delete_query.exec()){
        QString text = "删除记录人员数据库执行错误";
        LOG_ERROR(title+"-"+ text);
        logger->sendNotify(logger->LOGGERTYPE::ERROR,title,text);
    } else {
        LOG_INFO("删除记录人员");
    }
}

ReturnData Person::isExistsPerson(QString name, QString gender, QString birthday,QString weight)
{
    auto logger = Log::instance();
    ReturnData returnData;
    QMap<QString,QString> data;
    QString title = "是否存在记录人员";
    this->open();
    QSqlQuery exists_query;
    QString exists_sql = QString("select id, name, gender, birthday, weight from person where name='%1' and gender='%2' and birthday='%3'").arg(name,gender,birthday);
    exists_query.prepare(exists_sql);
    if(!exists_query.exec()){
        QString text = "查询记录人数数据库执行错误";
        LOG_ERROR(title + "-" + text);
        logger->sendNotify(logger->LOGGERTYPE::ERROR, title, text);
        returnData.code = "400";
        returnData.data = data;
        return returnData;
    } else {
        if(exists_query.last()){
            data["id"] = exists_query.value(0).toString();
            data["name"] = exists_query.value("name").toString();
            data["birthday"] = exists_query.value("birthday").toString();
            data["gender"] = exists_query.value("gender").toString();
            data["weight"] = exists_query.value("weight").toString();
            returnData.code = "200";
            returnData.data = data;
            return returnData;
        } else {
            returnData.code = "400";
            return returnData;
         }
    }
}

void updateName(QString id, QString name)
{
    auto logger = Log::instance();
    QString title ="更新记录人员";
    QSqlQuery query;
    QString update_sql = QString().arg("update person set name='%1' where id='%2'").arg(name,id);
    query.prepare(update_sql);
    if(!query.exec()){
        QString text = "更新记录人员名字数据库执行错误";
        LOG_ERROR(title+"-"+ text);
        logger->sendNotify(logger->LOGGERTYPE::ERROR,title,text);
    } else {
        LOG_INFO("更新记录人员名字");
    }
}
void updateBirthday(QString id, QString birthday)
{
    auto logger = Log::instance();
    QString title ="更新记录人员";
    QSqlQuery query;
    QString update_sql = QString().arg("update person set birthday='%1' where id='%2'").arg(birthday,id);
    query.prepare(update_sql);
    if(!query.exec()){
        QString text = "更新记录人员生日数据库执行错误";
        LOG_ERROR(title+"-"+ text);
        logger->sendNotify(logger->LOGGERTYPE::ERROR,title,text);
    } else {
        LOG_INFO("更新记录人员生日");
    }
}
void updateGender(QString id, QString gender)
{
    auto logger = Log::instance();
    QString title ="更新记录人员";
    QSqlQuery query;
    QString update_sql = QString().arg("update person set gender='%1' where id='%2'").arg(gender,id);
    query.prepare(update_sql);
    if(!query.exec()){
        QString text = "更新记录人员性别数据库执行错误";
        LOG_ERROR(title+"-"+ text);
        logger->sendNotify(logger->LOGGERTYPE::ERROR,title,text);
    } else {
        LOG_INFO("更新记录人员性别");
    }
}

void Person::updateWeight(QString id,QString weight)
{
    auto logger = Log::instance();
    QString title ="更新记录人员";
    QSqlQuery query;
    QString update_sql = QString().arg("update person set weight='%1' where id='%2'").arg(weight,id);
    query.prepare(update_sql);
    if(!query.exec()){
        QString text = "更新记录人员体重数据库执行错误";
        LOG_ERROR(title+"-"+ text);
        logger->sendNotify(logger->LOGGERTYPE::ERROR,title,text);
    } else {
        LOG_INFO("更新记录人员体重");
    }
}



