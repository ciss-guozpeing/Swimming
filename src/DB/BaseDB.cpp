#include "BaseDB.h"
#include <QDebug>

using namespace DB;
Base::Base()
{
    if(connectDB()){
        initTable();
    }
}

QSqlDatabase Base::driver()
{
    return m_db;
}

void Base::open()
{
    m_db.open();
}

void Base::close()
{
    m_db.close();
}

bool Base::connectDB()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        {
            m_db = QSqlDatabase::database("qt_sql_default_connection");
        }
        else {
            QFileInfo fi(QApplication::applicationDirPath() + "/DB/");
            bool isExists = fi.exists();
            if(!isExists){
                QDir dir;
                dir.mkdir(QApplication::applicationDirPath() + "/DB/");
            }
            m_db = QSqlDatabase::addDatabase("QSQLITE");
            m_db.setDatabaseName(QApplication::applicationDirPath() + "/DB/" + "Swimming.db");
        }

        if(!m_db.open())
        {
            qDebug()<<"error: failed to connect sqlite3 database."<< m_db.lastError();
            return false;
        }
        else {
            qDebug()<<"success to connect sqlite3 database.";
            return true;
        }
        m_db.close();
}

void Base::initTable()
{
    // person table
    open();
    QSqlQuery person_query(driver());
    QString person_sql = "create table if not exists person (id integer primary key autoincrement not null, \
                                                             name varchar(30) not null, \
                                                             birthday varchar(20) not null, \
                                                             gender varchar(5) not null, \
                                                             weight varchar(5))";
    person_query.prepare(person_sql);
    if (!person_query.exec()){
       qDebug() <<"person表不成功"<< person_query.lastError();
    } else{
       qDebug() << "person表成功";
    }
    person_query.finish();
    close();

   // user table
   open();
   QSqlQuery user_query(driver());
   QString user_sql = "create table if not exists user(id integer primary key autoincrement not null, \
                                                       username varchar(30) not null, \
                                                       password varchar(30) not null, \
                                                       isSupper bool not null, \
                                                       email varchar(30))";
   user_query.prepare(user_sql);
   if (!user_query.exec()){
       qDebug() <<"user表不成功"<< user_query.lastError();
   } else{
       qDebug() << "user表成功";
   }
   user_query.finish();
   close();

   // record table
   open();
   QSqlQuery record_query(driver());
   QString record_sql = "create table if not exists record(id integer primary key autoincrement not null, \
                                                           level varchar(30) not null, \
                                                           team varchar(30) not null , \
                                                           stage varchar(10) not null, \
                                                           stroke varchar(10) not null, \
                                                           strokeItem varchar(10) not null, \
                                                           distance integer not null, \
                                                           maxPower1 varchar(10) not null, \
                                                           maxPower2 varchar(10) not null, \
                                                           maxPower3 varchar(10) not null, \
                                                           maxPower varchar(10), \
                                                           relPower varchar(10), \
                                                           percentage varchar(10), \
                                                           contributionRate varchar(10), \
                                                           environment varchar(10), \
                                                           workspace varchar(10), \
                                                           createAt TIMESTAMP default (strftime('%Y/%m/%d','now','localtime')), \
                                                           updateAt numeric default (datetime('now','localtime')), \
                                                           personId interger, \
                                                           constraint fk_person_id foreign key(personId) references person(id) \
                                                                                  )";
   record_query.prepare(record_sql);
   if (!record_query.exec()){
       qDebug() <<"record表不成功"<< record_query.lastError();
   } else{
       qDebug() << "record表成功";
   }
   record_query.finish();
   close();
}
