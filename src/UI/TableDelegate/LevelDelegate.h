#ifndef LEVELDELEGATE_H
#define LEVELDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>

class LevelDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    LevelDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
};

#endif // LEVELDELEGATE_H
