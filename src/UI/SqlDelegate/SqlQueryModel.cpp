#include "SqlQueryModel.h"

SqlQueryModel::SqlQueryModel(QWidget *parent):QSqlQueryModel(parent)
{

}

QVariant SqlQueryModel::data(const QModelIndex & index, int role) const
{
    if(role == Qt::TextAlignmentRole){
        QVariant value = Qt::AlignCenter;
        return value;
    }
    return SqlQueryModel::data(index,role);
}
