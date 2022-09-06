#include "ViewPage.h"
#include "ui_viewpage.h"

#include "src/UI/TableView.h"
#include "src/UI/TableDelegate/ViewBase.h"
#include <QDebug>
static ViewPage* INSTANCE=nullptr;
QVector<QWidget*> ViewPage::m_showWidgets={};
ViewPage::ViewPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewPage)
{
    ui->setupUi(this);
    this->setWindowTitle("查看");
    this->setWindowIcon(QIcon(":/images/images/swimming.png"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint |Qt::WindowMaximizeButtonHint);

}

ViewPage::~ViewPage()
{
    delete ui;
}

ViewPage *ViewPage::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new ViewPage();
    }
    return INSTANCE;
}

void ViewPage::createShowMessage(QVector<int> rowIndexs)
{
    auto tableView = TableView::getInstance();

    int widgetCount = ui->gridLayout->count();
    for(int i=0;i<widgetCount;++i){
        QWidget* widget = m_showWidgets.at(widgetCount-i-1);
        m_showWidgets.remove(widgetCount-i-1);
        ui->gridLayout->removeWidget(widget);
        delete widget;
    }

    int rowSerial = 0;
    for(int i=0; i < rowIndexs.size(); i++){
        auto viewBase =  new ViewBase;
        QVector<QString> rowData;
        for(int j=0; j<tableView->model()->columnCount();j++){
           rowData.push_back(tableView->model()->item(rowIndexs.at(i),j)->text());
        }
        viewBase->setText(rowData);
        m_showWidgets.push_back(viewBase);

        if(i % 2 ==0){
            rowSerial = i / 2;
        }
        int columnSerial = i % 2;
        ui->gridLayout->addWidget(viewBase,rowSerial,columnSerial);
    }
}

QWidget* ViewPage::createSingleShowMessage()
{
    QWidget* widget = new QWidget;
    QLabel* name = new QLabel;
    name->setText("guozeping");
    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addWidget(name);
    widget->setLayout(hLayout);
    widget->setFixedHeight(250);
    return widget;
}
