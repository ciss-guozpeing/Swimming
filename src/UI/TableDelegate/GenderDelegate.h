#ifndef GENDERDELEGATE_H
#define GENDERDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>
class GenderDelegate:public QStyledItemDelegate
{
    Q_OBJECT
public:
    GenderDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
};

#endif // GENDERDELEGATE_H
