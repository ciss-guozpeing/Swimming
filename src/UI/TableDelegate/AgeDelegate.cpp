#include "AgeDelegate.h"

#include "src/Settings/TableSetting.h"
#include "src/DB/Record.h"
#include "src/UI/TableView.h"
#include <QDateEdit>
AgeDelegate::AgeDelegate() {}

QWidget* AgeDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QDateEdit* editor = new QDateEdit(parent);
    return editor;
}

void AgeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const
{
    auto tableView = TableView::getInstance();
    auto record =new DB::Record();
    QDateEdit* comBox = static_cast<QDateEdit*> (editor);
    record->setOldUpdateValue(tableView->proxyModel()->data(index).toString());
    record->setUpdateModelIndex(index);
    // 更新表格
    QDateTime curdate = QDateTime::currentDateTime();//获取系统现在的时间
    int curyear = curdate.toString("yyyy/MM/dd").split('/')[0].toInt();
    int biryear = comBox->text().split('/')[0].toUInt();
    QString age = QString::number(curyear-biryear);
    model->setData(index, age);
    // 更新数据库
    bool isSuccess = false;
    isSuccess = record->updateAge(comBox->text());
    if(!isSuccess){
        model->setData(index,tableView->proxyModel()->data(index).toString());
    }
    record->deleteLater();
}
