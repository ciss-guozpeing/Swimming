#ifndef MAXPOWERDELEGATE_H
#define MAXPOWERDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QDoubleSpinBox>

class MaxPowerDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    MaxPowerDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
};

#endif // MAXPOWERDELEGATE_H
