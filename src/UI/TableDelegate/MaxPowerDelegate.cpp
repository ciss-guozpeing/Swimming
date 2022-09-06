#include "MaxPowerDelegate.h"

#include "src/Settings/TableSetting.h"
#include "src/DB/Record.h"
#include "src/UI/TableView.h"

MaxPowerDelegate::MaxPowerDelegate()
{

}

QWidget* MaxPowerDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    QDoubleSpinBox* editor = new QDoubleSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(1000);
    return editor;
}

void MaxPowerDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    auto tableView = TableView::getInstance();
    auto record =new DB::Record();
    QDoubleSpinBox* doubleSpinxBox = static_cast<QDoubleSpinBox*> (editor);
    record->setOldUpdateValue(tableView->proxyModel()->data(index).toString());
    record->setUpdateModelIndex(index);
    // 更新表格
    model->setData(index,doubleSpinxBox->text());
    // 更新数据库
    bool isSuccess = false;
    isSuccess = record->updateMaxPower(doubleSpinxBox->text(), QString::number(index.column()));
    if(!isSuccess){
        model->setData(index,tableView->proxyModel()->data(index).toString());
    }
    record->deleteLater();
}
