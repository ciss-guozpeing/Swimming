#include "ClusterPage.h"
#include "ui_clusterpage.h"

#include "src/Settings/TableSetting.h"
static ClusterPage* INSTANCE=nullptr;
ClusterPage::ClusterPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClusterPage)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel(ui->tableView);
    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    auto tableSetting = TableSetting::getInstance();
    for(int i=0; i<tableSetting->getTableHeaderData().length()-1; ++i){
        QStandardItem* aItem = new QStandardItem(tableSetting->getTableHeaderData().at(i));
        m_model->setHorizontalHeaderItem(i,aItem);
    }
}

ClusterPage::~ClusterPage()
{
    delete ui;
}
ClusterPage *ClusterPage::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new ClusterPage();
    }
    return INSTANCE;
}

QStandardItemModel* ClusterPage::model()
{
    return m_model;
}
