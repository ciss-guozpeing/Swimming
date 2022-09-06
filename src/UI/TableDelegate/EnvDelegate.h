#ifndef ENVDELEGATE_H
#define ENVDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>

class EnvDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    EnvDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
};

#endif // ENVDELEGATE_H
