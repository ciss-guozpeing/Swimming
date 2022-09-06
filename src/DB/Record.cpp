#include "Record.h"
#include "src/Common/Log.h"
#include "src/UI/TableView.h"
#include "src/Settings/TableSetting.h"
using namespace DB;
Record::Record():Base(){}

bool Record::_isExistsRecord(QString name, QString birthday, QString gender,QString stroke,QString type,QString create_at)
{
    auto logger = Log::instance();
    QString person_id;
    QSqlQuery select_person_query;
    QString select_person_sql = QString("select id from person where name = '%1' and gender='%2' and birthday='%3'").arg(name,gender,birthday);
    select_person_query.prepare(select_person_sql);
    if(!select_person_query.exec()){
        logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"创建记录","查询记录人员失败",true);
        return true;
    } else{
        select_person_query.next();
        person_id = select_person_query.value(0).toString();
        LOG_INFO(QString("创建记录-查询记录人员id'%1'").arg(person_id));
    }

    QSqlQuery select_query;
    QString select_sql = QString("select count(stroke) from person LEFT JOIN  record on record.person_id = '%1' WHERE record.stroke = '%2'  and record.type='%3' and record.create_at='%4'").arg(person_id,stroke,type,create_at);
    select_query.prepare(select_sql);
    if(!select_query.exec()){
        logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"创建记录","创建记录失败",true);
        return true;
    } else {
        select_query.next();
        if(select_query.value(0).toInt()){
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"创建记录","同步数据库记录失败,当日记录已存在",true);
            return true;
        } else{
            LOG_INFO("创建记录-记录数据不存在,可以创建");
            return false;
        }
    }
}

QMap<QString,int> Record::_isExistsUpdateRecord(QString name, QString birthday, QString gender,QString stroke,QString type,QString create_at)
{
    QMap<QString,int> result;
    auto logger = Log::instance();
    QString person_id;

    QSqlQuery select_person_query;
    QString select_person_sql = QString("select id from person where name = '%1' and gender='%2' and birthday='%3'").arg(name,gender,birthday);
    select_person_query.prepare(select_person_sql);
    if(!select_person_query.exec()){
        logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"更新记录","查询记录人员失败",true);
        result["person_id"] = -1;
        result["isExists"] = false;
        return result;
    } else{
        select_person_query.next();
        person_id = select_person_query.value(0).toString();
        LOG_INFO(QString("创建记录-查询记录人员id'%1'").arg(person_id));
    }

    QSqlQuery select_query;
    QString select_sql = QString("select count(stroke) from person LEFT JOIN  record on record.person_id = '%1' WHERE record.stroke = '%2'  and record.type='%3' and record.create_at='%4'").arg(person_id,stroke,type,create_at);
    select_query.prepare(select_sql);
    if(!select_query.exec()){
        logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"更新记录","查询记录失败",true);
        result["person_id"] = -1;
        result["isExists"] = false;
        return result;
    } else {
        select_query.next();
        if(select_query.value(0).toInt()){
            result["person_id"] = person_id.toInt();
            result["isExists"] = true;
            return result;
        } else{
            logger->sendLogMessage(logger->LOGGERTYPE::WARN,"更新记录","更新记录不存在",true);
            result["person_id"] = -1;
            result["isExists"] = false;
            return result;
        }
    }
}

QMap<QString,int> Record::_isExistsDeleteRecord(QString name, QString birthday, QString gender,QString stroke,QString type,QString create_at)
{
    auto logger = Log::instance();
    QString person_id;
    QMap<QString,int> result;

    QSqlQuery select_person_query;
    QString select_person_sql = QString("select id from person where name = '%1' and gender='%2' and birthday='%3'").arg(name,gender,birthday);
    select_person_query.prepare(select_person_sql);
    if(!select_person_query.exec()){
        logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"更新记录","查询记录人员失败",true);
        result["isExists"] = 0;
        result["person_id"] = person_id.toInt();
        return result;
    } else{
        select_person_query.next();
        person_id = select_person_query.value(0).toString();
        LOG_INFO(QString("创建记录-查询记录人员id'%1'").arg(person_id));
    }

    QSqlQuery select_query;
    QString select_sql = QString("select count(stroke) from person LEFT JOIN  record on record.person_id = '%1' WHERE record.stroke = '%2'  and record.type='%3' and record.create_at='%4'").arg(person_id,stroke,type,create_at);
    select_query.prepare(select_sql);
    if(!select_query.exec()){
        logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"更新记录","查询记录失败",true);
        result["isExists"] = 0;
        result["person_id"] = person_id.toInt();
        return result;
    } else {
        select_query.next();
        if(select_query.value(0).toInt()){
            result["isExists"] = 1;
            result["person_id"] = person_id.toInt();
            return result;
        } else{
            logger->sendLogMessage(logger->LOGGERTYPE::WARN,"更新记录","更新记录不存在",true);
            result["isExists"] = 0;
            result["person_id"] = person_id.toInt();
            return result;
        }
    }
}

void Record::createRecord(QString name, QString birthday, QString gender,QString level, QString team,
                          QString stage,QString stroke,QString type,QString distance, QString maxpower1, QString maxpower2,
                          QString maxpower3,QString environment,QString create_at)
{
    auto logger = Log::instance();
    this->open();
    bool isExists = this->_isExistsRecord(name,birthday,gender,stroke,type,create_at);
    if(!isExists){
        QString person_id;
        QSqlQuery select_person_query;
        QString select_person_sql = QString("select id from person where name = '%1' and gender='%2' and birthday='%3'").arg(name,gender,birthday);
        select_person_query.prepare(select_person_sql);
        if(!select_person_query.exec()){
        logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"创建记录","创建记录失败",true);
        } else{
            select_person_query.next();
            person_id = select_person_query.value(0).toString();
        }

        // 插入
        QSqlQuery create_query;
        QString create_sql = QString("INSERT into record (level,team,stage,stroke,type,distance,maxpower1,maxpower2,maxpower3,"
                                     "environment,person_id) VALUES('%1','%2','%3','%4','%5','%6','%7','%8','%9','%10','%11')").arg(level,team,stage,stroke,type,
                                                                                                                                     distance,maxpower1,maxpower2,                                                                                                                          maxpower3,environment,person_id);
        create_query.prepare(create_sql);
        if(!create_query.exec()){
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"创建记录","创建记录失败",true);
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::INFO,"创建记录","创建记录成功",true);
        }
    }
    this->close();
}

void Record::updateRecord(QString name, QString birthday, QString gender,QString stroke,QString type,
                          QString maxPower,QString relPower,QString percentage,QString contribution_rate)
{
    auto logger = Log::instance();
    this->open();
    QString person_id;
    QSqlQuery select_person_query;
    QString select_person_sql = QString("select id from person where name = '%1' and gender='%2' and birthday='%3'").arg(name,gender,birthday);
    select_person_query.prepare(select_person_sql);
    if(!select_person_query.exec()){
        logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"","",true);
    } else{
        select_person_query.next();
        person_id = select_person_query.value(0).toString();
    }

    QSqlQuery update_query;
    QString update_sql = QString("UPDATE record SET maxpower='%1',relpower='%2',percentage='%3',contribution_rate='%4' "
                                 "WHERE person_id='%5' and stroke='%6' and type='%7'").arg(maxPower,relPower,percentage,contribution_rate,person_id,stroke,type);
    update_query.prepare(update_sql);
    if(!update_query.exec()){
        logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"更新记录","",true);
    } else {
        logger->sendLogMessage(logger->LOGGERTYPE::INFO,"更新记录","更新记录成功",false);
    }
    this->close();
}

void Record::deleteRecord(QVector<int> rowIndexs)
{
    auto logger = Log::instance();
    this->open();
    auto tableView = TableView::getInstance();
    for(int i=0; i<rowIndexs.size(); i++){
        QString name = tableView->proxyModel()->index(rowIndexs.at(i),2).data().toString();
        QString birthday = tableView->proxyModel()->index(rowIndexs.at(i),0).data().toString().split("::").at(1);
        QString gender = tableView->proxyModel()->index(rowIndexs.at(i),3).data().toString();
        QString stroke = tableView->proxyModel()->index(rowIndexs.at(i),9).data().toString();
        QString type = tableView->proxyModel()->index(rowIndexs.at(i),10).data().toString();
        QString create_at = tableView->proxyModel()->index(rowIndexs.at(i),1).data().toString().split("::").at(1);
        QMap<QString,int> result = this->_isExistsDeleteRecord(name, birthday, gender, stroke, type, create_at);
        QString person_id = QString::number(result["person_id"]);
        bool isExists = result["isExists"];
        if(isExists){
            QSqlQuery delete_query;
            QString delete_sql = QString("delete from record where stroke='%1' and type='%2' and person_id='%3'").arg(stroke,type,person_id);
            delete_query.prepare(delete_sql);
            if(!delete_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,"删除记录","删除记录失败",false);
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,"删除记录","删除记录成功",false);
            }
        }
    }
    this->close();
}

void Record::setUpdateModelIndex(const QModelIndex index)
{
    m_modelIndex = index;
}

QModelIndex Record::updateModelIndex()
{
    return m_modelIndex;
}

void Record::setOldUpdateValue(QString value)
{
    m_oldUpdateValue = value;
}

bool Record::updateName(QString name)
{
    return true;
}
bool Record::updateGender(QString gender)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();
    QString oldGender = m_oldUpdateValue;
    if(oldGender!=gender){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString stroke = tableView->model()->item(rowSerial,9)->text();
        QString strokeItem = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,oldGender,stroke,strokeItem,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;
            QString update_sql = QString("update person set gender='%1' where person.gender='%2' and person.id='%3'").arg(gender,oldGender,person_id);
            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(gender),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(gender),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(gender),true);
            return false;
        }
    } else {
        return false;
    }
    return true;
}
bool Record::updateWeight(QString weight)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();
    QString oldWeight = m_oldUpdateValue;
    if(oldWeight!=weight){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString gender = tableView->model()->item(rowSerial,3)->text();
        QString stroke = tableView->model()->item(rowSerial,9)->text();
        QString strokeItem = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,gender,stroke,strokeItem,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;

            QString update_sql = QString("update person SET weight='%1' FROM (SELECT * FROM record WHERE record.stroke='%2' and record.type='%3') WHERE person.id = '%4'").arg(weight,stroke,strokeItem,person_id);
            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(weight),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(weight),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(weight),true);
            return false;
        }
    } else {
        return false;
    }

    return true;
}
bool Record::updateAge(QString age)
{
    return true;
}
bool Record::updateLevel(QString level)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();
    QString oldLevel = m_oldUpdateValue;
    if(oldLevel!=level){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString gender = tableView->model()->item(rowSerial,3)->text();
        QString stroke = tableView->model()->item(rowSerial,9)->text();
        QString strokeItem = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,gender,stroke,strokeItem,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;
            QString update_sql = QString("update record set level='%1' where record.level='%2' and record.person_id='%3'").arg(level,oldLevel,person_id);
            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(level),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(level),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(level),true);
            return false;
        }
    } else {
        return false;
    }

    return true;
}

bool Record::updateTeam(QString team)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();
    QString oldTeam = m_oldUpdateValue;
    if(oldTeam!=team){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString gender = tableView->model()->item(rowSerial,3)->text();
        QString stroke = tableView->model()->item(rowSerial,9)->text();
        QString strokeItem = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,gender,stroke,strokeItem,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;
            QString update_sql = QString("update record set team='%1' where record.team='%2' and record.person_id='%3'").arg(team,oldTeam,person_id);
            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(team),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(team),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(team),true);
            return false;
        }
    } else {
        return false;
    }
    return true;
}
bool Record::updateStage(QString stage)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();
    QString oldStage = m_oldUpdateValue;
    if(oldStage!=stage){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString gender = tableView->model()->item(rowSerial,3)->text();
        QString stroke = tableView->model()->item(rowSerial,9)->text();
        QString strokeItem = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,gender,stroke,strokeItem,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;
            QString update_sql = QString("update record set stage='%1' where record.stage='%2' and record.person_id='%3'").arg(stage,oldStage,person_id);
            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(stage),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(stage),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(stage),true);
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool Record::updateStroke(QString stroke)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();

    QString oldStroke = m_oldUpdateValue;

    if(oldStroke!=stroke){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString gender = tableView->model()->item(rowSerial,3)->text();
        QString type = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,gender,oldStroke,type,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;
            QString update_sql = QString("update record set stroke='%1' where record.stroke='%2' and record.person_id='%3'").arg(stroke,oldStroke,person_id);
            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(stroke),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(stroke),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(stroke),true);
            return false;
        }

    } else {
        LOG_INFO("");
        return false;
    }
}

bool Record::updateStrokeItem(QString strokeItem)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();
    QString oldStrokeItem = m_oldUpdateValue;
    if(oldStrokeItem!=strokeItem){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString gender = tableView->model()->item(rowSerial,3)->text();
        QString stroke = tableView->model()->item(rowSerial,9)->text();
        QString strokeItem = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,gender,stroke,oldStrokeItem,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;
            QString update_sql = QString("update record set type='%1' where record.type='%2' and record.stroke='%3' and record.person_id='%4'").arg(strokeItem,oldStrokeItem,stroke,person_id);
            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(strokeItem),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(strokeItem),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(strokeItem),true);
            return false;
        }
    } else {
        LOG_INFO(QString("泳姿类型相等'%1','%2'").arg(oldStrokeItem).arg(strokeItem))
        return false;
    }
    return true;
}

bool Record::updateDistance(QString distance)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();
    QString oldDistance = m_oldUpdateValue;
    if(oldDistance!=distance){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString gender = tableView->model()->item(rowSerial,3)->text();
        QString stroke = tableView->model()->item(rowSerial,9)->text();
        QString strokeItem = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,gender,stroke,strokeItem,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;
            QString update_sql = QString("update record set distance='%1' where record.distance='%2' and record.person_id='%3'").arg(distance,oldDistance,person_id);
            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(distance),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(distance),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(distance),true);
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool Record::updateMaxPower(QString maxPower, QString text)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();
    QString oldMaxPower = m_oldUpdateValue;
    if(oldMaxPower!=maxPower){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString gender = tableView->model()->item(rowSerial,3)->text();
        QString stroke = tableView->model()->item(rowSerial,9)->text();
        QString strokeItem = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,gender,stroke,strokeItem,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;
            QString update_sql;
            if(text=="12"){
                update_sql = QString("update record set maxpower1='%1' where record.maxpower1='%2' and record.person_id='%3'").arg(maxPower,oldMaxPower,person_id);
            } else if(text=="13"){
                update_sql = QString("update record set maxpower2='%1' where record.maxpower2='%2' and record.person_id='%3'").arg(maxPower,oldMaxPower,person_id);
            } else if(text=="14"){
                update_sql = QString("update record set maxpower3='%1' where record.maxpower3='%2' and record.person_id='%3'").arg(maxPower,oldMaxPower,person_id);
            }

            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(maxPower),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(maxPower),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(maxPower),true);
            return false;
        }
    } else {
        return false;
    }
    return true;
}

bool Record::updateEnv(QString env)
{
    auto logger = Log::instance();
    auto tableView = TableView::getInstance();
    int rowSerial = updateModelIndex().row();
    QString oldEnv = m_oldUpdateValue;
    if(oldEnv!=env){
        QString name = tableView->model()->item(rowSerial,2)->text();
        QString birthday = tableView->model()->item(rowSerial,0)->text().split("::").at(1);
        QString gender = tableView->model()->item(rowSerial,3)->text();
        QString stroke = tableView->model()->item(rowSerial,9)->text();
        QString strokeItem = tableView->model()->item(rowSerial,10)->text();
        QString create_at = tableView->model()->item(rowSerial,1)->text().split("::").at(1);

        this->open();
        QMap<QString,int> result = this->_isExistsUpdateRecord(name,birthday,gender,stroke,strokeItem,create_at);
        if(result["isExists"]){
            QString person_id = QString::number(result["person_id"]);
            QSqlQuery update_query;
            QString update_sql = QString("update record set environment='%1' where record.environment='%2' and record.person_id='%3'").arg(env,oldEnv,person_id);
            update_query.prepare(update_sql);
            if(!update_query.exec()){
                logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(env),true);
                return false;
            } else {
                logger->sendLogMessage(logger->LOGGERTYPE::INFO,QString("%1").arg("更新记录"),QString("更新'%1'").arg(env),true);
                return true;
            }
        } else {
            logger->sendLogMessage(logger->LOGGERTYPE::ERROR,QString("%1").arg("更新记录"),QString("更新'%1'失败").arg(env),true);
            return false;
        }
    } else {
        return false;
    }
    return true;
}

