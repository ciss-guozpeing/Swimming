#ifndef HISTDATAPAGE_H
#define HISTDATAPAGE_H

#include <QWidget>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QAction>
#include <QToolButton>

#include "src/DB/BaseDB.h"

namespace Ui {
class HistDataPage;
}

class HistDataPage : public QWidget
{
    Q_OBJECT
    QSqlQueryModel* m_queryModel;
    QSqlTableModel* m_personModel;
    QSqlTableModel* m_userModel;
public:
    explicit HistDataPage(QWidget *parent = nullptr);
    ~HistDataPage();
    static HistDataPage *getInstance();
    QSqlTableModel* personModel();
    QSqlTableModel* userModel();
    QSqlQueryModel* queryModel();

    void setPersonModel();
    void setUserModel();
    void setQueryModel();

private slots:
    void on_recordBtn_clicked();

    void on_personBtn_clicked();

    void on_userBtn_clicked();

private:
    Ui::HistDataPage *ui;
};

#endif // HISTDATAPAGE_H
