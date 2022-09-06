#ifndef STROKEITEMDELEGATE_H
#define STROKEITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>

class StrokeItemDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    StrokeItemDelegate();
    static StrokeItemDelegate *getInstance();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
//    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // STROKEITEMDELEGATE_H
