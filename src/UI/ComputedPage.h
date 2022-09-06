#ifndef COMPUTEDPAGE_H
#define COMPUTEDPAGE_H

#include <QWidget>
#include <QChartView>
#include <QtCharts>
#include <QHBoxLayout>
using namespace QtCharts;
QT_CHARTS_USE_NAMESPACE


namespace Ui {
class ComputedPage;
}

class ComputedPage : public QWidget
{
    Q_OBJECT
    QBarSet *m_set0;
    QBarSet *m_set1;
    QBarSet *m_set2;
    QBarSet *m_set3;
    QBarSet *m_set4;
    QValueAxis* m_axisY;
    QChartView* m_barView;
    QBarSeries* m_series;
    QMap<QString,QVector<QBarSet*>> m_all_barSet_Vec;
    QMap<QString,QBarSeries*> m_all_barSeries_Vec;
    QMap<QString,QChartView*> m_all_chartView;
    QMap<QString,QHBoxLayout*> m_all_ChartLayouts;
public:
    explicit ComputedPage(QWidget *parent = nullptr);
    ~ComputedPage();
    static ComputedPage *getInstance();

    void personStatistics();
    void createSinglePersonChart(QString key);

    void updatePersonStatistics(QMap<QString,QVector<int>> personStatistics);
    void updateSinglePersonStatistics(QMap<QString,QMap<QString,QVector<QVector<double>>>> result);

    void deleteSinglePersonChart(QString key);

private:
    Ui::ComputedPage *ui;
};

#endif // COMPUTEDPAGE_H
