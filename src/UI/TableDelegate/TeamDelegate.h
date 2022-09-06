#ifndef TEAMDELEGATE_H
#define TEAMDELEGATE_H
#include <QObject>
#include <QStyledItemDelegate>
#include <QComboBox>

class TeamDelegate: public QStyledItemDelegate
{
    Q_OBJECT
public:
    TeamDelegate();
    virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const override;
};

#endif // TEAMDELEGATE_H
