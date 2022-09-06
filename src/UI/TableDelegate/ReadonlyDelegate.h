#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#include <QItemDelegate>
class ReadOnlyDelegate:public QItemDelegate
{
public:
    ReadOnlyDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
};

#endif // READONLYDELEGATE_H
