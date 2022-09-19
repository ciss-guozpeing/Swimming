#ifndef TABLEDATA_H
#define TABLEDATA_H

#include <QString>
#include <QVector>
#include <QMap>

typedef QMap<QString,QMap<QString,QMap<QString,QVector<double>>>> DataType;

class TableData
{
    QString m_person;
    QString m_weight;
    QVector<QString> m_strokes;
    QMap<QString,QVector<QString>> m_strokeItems;
    QVector<double> m_values;
    DataType m_data = {
        {"自由泳",{{"自腿",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"自手",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"自配合",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"蹬边滑行",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}}}},
        {"仰泳",{{"仰腿",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"仰手",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"仰配合",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"海豚腿(仰卧)",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"蹬边滑行",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}}}},
        {"蛙泳",{{"蛙腿",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"蛙手",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"蛙配合",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"蹬边滑行",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}}}},
        {"蝶泳",{{"蝶腿",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"蝶手",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"蝶配合",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"海豚腿(俯卧)",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}},{"蹬边滑行",{{"5",{0,0,0,0,0,0,0}},{"7",{0,0,0,0,0,0,0}}}}}}
    };
public:
    explicit TableData(QString person,QString weight,QString stroke, QString strokeItem, QString distance,QVector<double> values);

    QString Person();
    QString weight();
    QVector<double> Values(QString stroke, QString strokeItem, QString distance);
    void setValues(QString stroke, QString strokeItem, QString distance, QVector<double> values);

};

#endif // TABLEDATA_H
