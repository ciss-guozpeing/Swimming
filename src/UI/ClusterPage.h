#ifndef CLUSTERPAGE_H
#define CLUSTERPAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QStandardItem>

namespace Ui {
class ClusterPage;
}

class ClusterPage : public QWidget
{
    Q_OBJECT
    QStandardItemModel* m_model;
public:
    explicit ClusterPage(QWidget *parent = nullptr);
    ~ClusterPage();
    static ClusterPage *getInstance();
    QStandardItemModel* model();

private:
    Ui::ClusterPage *ui;
};

#endif // CLUSTERPAGE_H
