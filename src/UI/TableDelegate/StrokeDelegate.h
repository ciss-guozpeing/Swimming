#ifndef STROKEDELEGATE_H
#define STROKEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>
#include <QString>

#include "StrokeItemDelegate.h"

class StrokeDelegate: public QStyledItemDelegate

{
    Q_OBJECT
    StrokeItemDelegate* m_strokeItemDelegate;
    QStringList m_StrokeItem;
public:
    static StrokeDelegate *getInstance();
    explicit StrokeDelegate();

    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
    QStringList getStrokeItem();
public slots:
    void OnComboxTextChanged(QString text);
};


#endif // STROKEDELEGATE_H
