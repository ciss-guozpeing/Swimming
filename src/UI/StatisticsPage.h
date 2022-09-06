#ifndef STATISTICSPAGE_H
#define STATISTICSPAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QStandardItem>

namespace Ui {
class StatisticsPage;
}

class StatisticsPage : public QWidget
{
    Q_OBJECT
    QStandardItemModel* m_model;
public:
    explicit StatisticsPage(QWidget *parent = nullptr);
    ~StatisticsPage();
    static StatisticsPage *getInstance();
    QStandardItemModel* model();
private:
    Ui::StatisticsPage *ui;
};

#endif // STATISTICSPAGE_H
