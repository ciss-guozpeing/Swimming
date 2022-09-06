#include "StrokeItemDelegate.h"

#include "src/Settings/TableSetting.h"
#include "StrokeDelegate.h"
#include "src/UI/TableView.h"
#include "src/DB/Record.h"

#include <QDebug>
static StrokeItemDelegate* INSTANCE=nullptr;

StrokeItemDelegate::StrokeItemDelegate()
{

}

StrokeItemDelegate *StrokeItemDelegate::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new StrokeItemDelegate();
    }
    return INSTANCE;
}

QWidget* StrokeItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto strokeDelgegate = StrokeDelegate::getInstance();
    QComboBox* editor = new QComboBox(parent);

    editor->addItems(strokeDelgegate->getStrokeItem());
    return editor;
}

void StrokeItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    auto tableView = TableView::getInstance();
    auto record =new DB::Record();
    QComboBox* comBox = static_cast<QComboBox*> (editor);
    qDebug() << tableView->proxyModel()->data(index).toString();
    record->setOldUpdateValue(tableView->proxyModel()->data(index).toString());
    record->setUpdateModelIndex(index);
    // 更新表格
    model->setData(index,comBox->currentText());
    qDebug() <<comBox->currentText() ;
    // 更新数据库
    bool isSuccess = false;
    isSuccess = record->updateStrokeItem(comBox->currentText());
    if(!isSuccess){
        model->setData(index,tableView->proxyModel()->data(index).toString());
    }
    record->deleteLater();
}




