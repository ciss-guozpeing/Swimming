#include "ComputedChart.h"
#include <QDebug>
#include <QThread>
ComputedChartRunable::ComputedChartRunable(QObject *parent)
    : QObject{parent}
{

}

void ComputedChartRunable::run()
{
    int i = 10;
    while (i--) {
        qDebug() << "线程id："<< QThread::currentThreadId()<< QString(":剩余%1").arg(i);
        QThread::sleep(1);
    }
}
