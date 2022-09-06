#ifndef DISTANCEDELEGATE_H
#define DISTANCEDELEGATE_H


#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>
class DistanceDelegate:public QStyledItemDelegate
{
    Q_OBJECT
public:
    DistanceDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
};

#endif // DISTANCEDELEGATE_H
