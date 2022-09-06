#ifndef BASEDB_H
#define BASEDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlRecord>

namespace DB{
    class Base: public QObject
    {
        Q_OBJECT
    private:
        QSqlDatabase m_db;

    public:
        Base();
        QSqlDatabase driver();
        bool connectDB();
        void initTable();
        void open();
        void close();
    };
}

#endif // BASEDB_H
