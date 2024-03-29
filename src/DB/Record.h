﻿#ifndef RECORD_H
#define RECORD_H

#include "BaseDB.h"
#include "src/Common/ReturnData.h"

#include <QModelIndex>

namespace DB{
    class Record: public Base
    {
        Q_OBJECT;
        QModelIndex m_modelIndex;
        QString m_oldUpdateValue;
        bool _isExistsRecord(QString name, QString birthday, QString gender,QString stroke,QString type,QString create_at);
        ReturnData isExistsRecord(QString stroke, QString strokeItem, QString distance, QString createAt, QString personId);

        QMap<QString,QString> isExistsCreateRecord(QString name, QString bitr);
        QMap<QString,int> _isExistsUpdateRecord(QString name, QString birthday, QString gender,QString stroke,QString type,QString create_at);
        QMap<QString,int> _isExistsDeleteRecord(QString name, QString birthday, QString gender,QString stroke,QString type,QString create_at);

    public:
        Record();
        void createRecord(QString personId, QString level, QString team, QString stage,QString stroke,
                          QString strokeItem,QString distance, QString maxpower1, QString maxpower2,
                          QString maxpower3,QString environment, QString createAt);

        void updateRecord(QString name, QString birthday, QString gender,QString stroke,QString type,
                          QString maxPower,QString relPower,QString percentage,QString contribution_rate);

        void setUpdateModelIndex(const QModelIndex index);
        QModelIndex updateModelIndex();
        void deleteRecord(QVector<int> rowIndexs);

    public slots:
        bool updateName(QString name);
        bool updateGender(QString gender);
        bool updateWeight(QString weight);
        bool updateAge(QString age);
        bool updateLevel(QString level);
        bool updateTeam(QString team);
        bool updateStage(QString stage);
        bool updateStroke(QString stroke);
        bool updateStrokeItem(QString strokeItem);
        bool updateDistance(QString distance);
        bool updateMaxPower(QString maxPower, QString text);
        bool updateEnv(QString env);
        void setOldUpdateValue(QString value);

        void updateRecord(QStringList record);

    };
}

#endif // RECORD_H
