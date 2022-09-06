#ifndef COMPUTEDCHART_H
#define COMPUTEDCHART_H

#include <QObject>
#include <QRunnable>

class ComputedChartRunable : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit ComputedChartRunable(QObject *parent = nullptr);
protected:
    void run();

signals:

};

#endif // COMPUTEDCHART_H
