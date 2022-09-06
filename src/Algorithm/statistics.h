#ifndef STATISTICS_H
#define STATISTICS_H

#include <QStringList>
#include <algorithm>
#include <math.h>

class Statistics
{
public:
    static Statistics *getInstance();
    Statistics();
    QString getMaxPower(QVector<double> vec);
    QString getRelativePower(QString maxPower, QString weight);
    QString getPercentage(QString maxPower, QString typeTOPower);
    QString getContribute(QString maxPower, double hl);

    QString getMaxValue(QVector<double> vec);
    QString getMinValue(QVector<double> vec);
    QString getAverageValue(QVector<double> vec);
    QString getStandardDev(QVector<double> vec);
};

#endif // STATISTICS_H
