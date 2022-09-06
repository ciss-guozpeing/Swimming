#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QWidget>
class SqlQueryModel: public QSqlQueryModel
{
public:
    SqlQueryModel(QWidget* parent=nullptr);
    //重写基类的虚函数
    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
};

#endif // SQLQUERYMODEL_H
