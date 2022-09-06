#ifndef WEIGHTDELEGATE_H
#define WEIGHTDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QDoubleSpinBox>

class WeightDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    WeightDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
};

#endif // WEIGHTDELEGATE_H
