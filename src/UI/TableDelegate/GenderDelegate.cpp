#include "GenderDelegate.h"

#include "src/Settings/TableSetting.h"
#include "src/DB/Record.h"
#include "src/UI/TableView.h"

GenderDelegate::GenderDelegate() {}

QWidget* GenderDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QComboBox* editor = new QComboBox(parent);
    editor->addItems(QStringList() <<"男" << "女");
    return editor;
}

void GenderDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    auto tableView = TableView::getInstance();
    auto record =new DB::Record();
    QComboBox* comBox = static_cast<QComboBox*> (editor);
    record->setOldUpdateValue(tableView->proxyModel()->data(index).toString());
    record->setUpdateModelIndex(index);
    // 更新表格
    model->setData(index,comBox->currentText());
    // 更新数据库
    bool isSuccess = false;
    isSuccess = record->updateGender(comBox->currentText());
    if(!isSuccess){
        model->setData(index,tableView->proxyModel()->data(index).toString());
    }
    record->deleteLater();
}
