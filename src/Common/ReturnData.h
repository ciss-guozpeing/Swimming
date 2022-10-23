#ifndef RETURNDATA_H
#define RETURNDATA_H
#include <QMetaType>
#include <QMap>
#include <QString>
struct ReturnData{
    QString code;
    QMap<QString,QString> data;
};
Q_DECLARE_METATYPE(ReturnData);
#endif // RETURNDATA_H
