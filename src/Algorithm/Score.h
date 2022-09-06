#ifndef SORE_H
#define SORE_H

#include <QObject>
#include <QMap>
#include <QVector>

#include "math.h"

#include "src/UI/TableDelegate/TableData.h"

class Score
{
    QMap<QString,QMap<QString,QMap<QString,QVector<double>>>> defaultMode = {
        {"自由泳",{{"自腿",{{"5",{}},{"7",{}}}},{"自手",{{"5",{}},{"7",{}}}},{"自配合",{{"5",{}},{"7",{}}}},{"蹬边滑行",{{"5",{}},{"7",{}}}}}},
        {"仰泳",{{"仰腿",{{"5",{}},{"7",{}}}},{"仰手",{{"5",{}},{"7",{}}}},{"仰配合",{{"5",{}},{"7",{}}}},{"海豚腿(仰卧)",{{"5",{}},{"7",{}}}},{"蹬边滑行",{{"5",{}},{"7",{}}}}}},
        {"蛙泳",{{"蛙腿",{{"5",{}},{"7",{}}}},{"蛙手",{{"5",{}},{"7",{}}}},{"蛙配合",{{"5",{}},{"7",{}}}},{"蹬边滑行",{{"5",{}},{"7",{}}}}}},
        {"蝶泳",{{"蝶腿",{{"5",{}},{"7",{}}}},{"蝶手",{{"5",{}},{"7",{}}}},{"蝶配合",{{"5",{}},{"7",{}}}},{"海豚腿(俯卧)",{{"5",{}},{"7",{}}}},{"蹬边滑行",{{"5",{}},{"7",{}}}}}}
    };
    QMap<QString,QMap<QString,QMap<QString,QVector<double>>>> m_manScoreTeamMode = defaultMode;
    QMap<QString,QMap<QString,QMap<QString,QVector<double>>>> m_womanScoreTeamMode = defaultMode;


    QStringList m_commonScoreStandard;
public:
    Score();
    static Score *getInstance();
    void setScoreTeamStandard(QMap<QString,TableData*> tableDatas);
    QString teamModelScore(QString gender, QString stroke, QString strokeItem, QString distance, QString maxPower);

    void setScoreCommonStandard(QVector<QVector<QString>> scoreDatas);
    QString commonModeScore(QString gender, QString stroke, QString strokeItem, QString maxPower);

    static QMap<QString,QMap<QString,QVector<QString>>> m_manScoreCommonMode;
    static QMap<QString,QMap<QString,QVector<QString>>> m_womanScoreCommonMode;
};

#endif // SORE_H
