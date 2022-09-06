#ifndef AGEDELEGATE_H
#define AGEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
//#include <QDa
class AgeDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    AgeDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
};

#endif // AGEDELEGATE_H
