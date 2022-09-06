#include "TrainStageDelegate.h"

#include "src/Settings/TableSetting.h"
#include "src/DB/Record.h"
#include "src/UI/TableView.h"

TrainStageDelegate::TrainStageDelegate()
{

}
QWidget* TrainStageDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    auto tableSetting = TableSetting::getInstance();
    QComboBox* editor = new QComboBox(parent);
    editor->addItems(tableSetting->getTrainStage());
    return editor;
}

void TrainStageDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    auto tableView = TableView::getInstance();
    auto record =new DB::Record();
    QComboBox* comBox = static_cast<QComboBox*> (editor);
    record->setOldUpdateValue(tableView->proxyModel()->data(index).toString());
    record->setUpdateModelIndex(index);
    // 更新界面
    model->setData(index,comBox->currentText());
    // 更新数据库
    bool isSuccess = false;
    isSuccess = record->updateStage(comBox->currentText());
    if(!isSuccess){
        model->setData(index,tableView->proxyModel()->data(index).toString());
    }
    record->deleteLater();
}
