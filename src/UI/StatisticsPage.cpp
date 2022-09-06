#include "StatisticsPage.h"
#include "ui_statisticspage.h"
#include "src/Settings/TableSetting.h"

static StatisticsPage* INSTANCE=nullptr;

StatisticsPage::StatisticsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(ui->tableView);
    ui->tableView->setModel(m_model);
    auto tableSetting = TableSetting::getInstance();
    QStringList rowHeader = tableSetting->getStatisticalRowHeader();
    QStringList columnHeader = tableSetting->getStaticticalColHeader();
    ui->tableView->setMinimumWidth(this->width() / 3);
    for (int i=0; i<rowHeader.length(); i++) {// 设置行表头
        model()->setHorizontalHeaderItem(i,new QStandardItem(rowHeader[i]));
    }
    for (int i=0; i<columnHeader.length(); i++) {
        model()->setVerticalHeaderItem(i, new QStandardItem(columnHeader[i]));
    }
    for(int i=0; i<rowHeader.length(); i++){
        for (int j=0; j<columnHeader.length(); j++) {
            model()->setItem(i,j, new QStandardItem(""));
        }
    }
}

StatisticsPage::~StatisticsPage()
{
    delete ui;
}
StatisticsPage *StatisticsPage::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new StatisticsPage();
    }
    return INSTANCE;
}

QStandardItemModel* StatisticsPage::model()
{
    return m_model;
}
