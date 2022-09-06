#ifndef TRAINSTAGEDELEGATE_H
#define TRAINSTAGEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>

class TrainStageDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    TrainStageDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
};

#endif // TRAINSTAGEDELEGATE_H
