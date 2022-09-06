#include "WeightDelegate.h"

#include "src/Settings/TableSetting.h"
#include "src/DB/Record.h"
#include "src/UI/TableView.h"

WeightDelegate::WeightDelegate()
{

}

QWidget* WeightDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(100);
    return editor;
}

void WeightDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    auto tableView = TableView::getInstance();
    auto record =new DB::Record();
    QDoubleSpinBox* doubleSpinBox = static_cast<QDoubleSpinBox*> (editor);
    record->setOldUpdateValue(tableView->proxyModel()->data(index).toString());
    record->setUpdateModelIndex(index);
    // 更新表格
    model->setData(index,doubleSpinBox->text());
    // 更新数据库
    bool isSuccess = false;
    isSuccess = record->updateWeight(doubleSpinBox->text());
    if(!isSuccess){
        model->setData(index,tableView->proxyModel()->data(index).toString());
    }
    record->deleteLater();
}
