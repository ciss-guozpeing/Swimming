#include "StrokeDelegate.h"

#include "StrokeItemDelegate.h"
#include "src/Settings/TableSetting.h"
#include "src/DB/Record.h"
#include "src/UI/TableView.h"
#include <QStandardItem>
#include <QDebug>

static StrokeDelegate* INSTANCE=nullptr;

StrokeDelegate::StrokeDelegate()
{
}

StrokeDelegate *StrokeDelegate::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new StrokeDelegate();
    }
    return INSTANCE;
}

QWidget* StrokeDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    Q_UNUSED(option);
    Q_UNUSED(index);
    auto tableSetting = TableSetting::getInstance();

    QComboBox* editor = new QComboBox(parent);
    connect(editor,SIGNAL(currentTextChanged(QString)),this,SLOT(OnComboxTextChanged(QString)));

    editor->addItems(tableSetting->getStroke());
    return editor;
}

void StrokeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    Q_UNUSED(editor);
}

void StrokeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    auto tableView = TableView::getInstance();
    auto record =new DB::Record();
    QComboBox* comBox = static_cast<QComboBox*> (editor);
    record->setOldUpdateValue(tableView->proxyModel()->data(index).toString());
    record->setUpdateModelIndex(index);
    model->setData(index,comBox->currentText());
    //TODO 判断表格中已经存在的数据
//    bool isExists = tableView->isExistsData("");
    bool isSuccess = false;
//    if(!isExists){
//        record->setUpdateModelIndex(index);
//        isSuccess = record->updateStroke(comBox->currentText());
//    }

    isSuccess = record->updateStroke(comBox->currentText());

    if(!isSuccess){
        model->setData(index,tableView->proxyModel()->data(index).toString());
    }
//    if(!isSuccess || !isExists){
//        model->setData(index,tableView->proxyModel()->data(index).toString());
//    }

    // 更新泳姿类型数据库
    int row = tableView->proxyModel()->mapToSource(index).row();
    int column = tableView->proxyModel()->mapToSource(index).column() + 1;
    QModelIndex strokeItemIndex= tableView->model()->indexFromItem(tableView->model()->item(row,column));
    qDebug() <<tableView->model()->data(strokeItemIndex).toString();
    record->setOldUpdateValue(tableView->model()->data(strokeItemIndex).toString());
    record->setUpdateModelIndex(strokeItemIndex);
    bool isSuccesss = record->updateStrokeItem("请选择");
    qDebug() << "泳姿类型" << isSuccesss;
    // 更新泳姿类型界面
    tableView->model()->setData(strokeItemIndex,"请选择");
    record->deleteLater();
}

void StrokeDelegate::OnComboxTextChanged(QString text)
{
    m_StrokeItem.clear();
    auto tableSetting = TableSetting::getInstance();
    m_StrokeItem = tableSetting->getStrokeItem()[text];
}

QStringList StrokeDelegate::getStrokeItem()
{
    return m_StrokeItem;
}

