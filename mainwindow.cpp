#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "src/Common/window.h"
#include "src/Common/Message.h"
#include "src/DB/Person.h"
#include "src/DB/Record.h"
#include "src/Settings/Settings.h"
#include "src/Settings/TableSetting.h"
#include "src/Settings/WindowSetting.h"
#include "src/UI/Help.h"
#include "src/UI/Login.h"
#include "src/UI/ComputedPage.h"
#include "src/UI/ClusterPage.h"
#include "src/UI/StatisticsPage.h"
#include "src/UI/ViewPage.h"
#include "src/UI/HistDataPage.h"
#include "src/Common/ThreadPool.h"
#include "src/Tasks/LoadTableData.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUI();
    this->setWindowTitle("主界面");
    this->setWindowState(Qt::WindowMaximized); //窗口最大化显示
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_QuitOnClose);
    this->setWindowIcon(QIcon(":/images/images/swimming.png"));

    connect(Login::getInstance(),SIGNAL(loginOnclicked(QString,bool)), this, SLOT(setUserName(QString,bool)));
    connect(Login::getInstance(),SIGNAL(showMainWindow()), this, SLOT(show()));
    connect(ui->mainSearch,SIGNAL(clicked()), this, SLOT(setKValue()));
    connect(m_actQuit,SIGNAL(triggered()),this,SLOT(actQuite_triggered()));
    connect(m_actAccount,SIGNAL(triggered()),this,SLOT(actAccount_triggered()));
    connect(ui->scoreComboBox,SIGNAL(currentIndexChanged(int)),tableView(),SLOT(setScoreMode(int)));
    connect(this,SIGNAL(sendTableDatas(QVector<QStringList>)),new LoadTableDataRunable,SLOT(receviedTableDatas(QVector<QStringList>)));
    connect(ui->nameSearchEditLint,SIGNAL(textChanged(QString)), this, SLOT(nameSearch(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::initUI()
{
    // 按钮
    ui->mainSettingPage->hide();

    // 用户名-头像
    QWidget* widget_spacer = new QWidget(this);
    widget_spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    ui->toolBar->addWidget(widget_spacer);

    // 用户名
    m_username = new QLabel(this);
    ui->toolBar->addWidget(m_username);
    // 头像
    QMenu* menu = new QMenu(this);
    m_profileBtn = new QPushButton(this);
    m_actProfile = new QAction("个人设置", this);
    m_actAccount = new QAction("开通账户", this);
    m_actQuit =    new QAction("退 出", this);
    menu->addAction(m_actProfile);
    menu->addSeparator();
    menu->addAction(m_actAccount);
    menu->addSeparator();
    menu->addAction(m_actQuit);
    menu->setWindowFlags(menu->windowFlags() | Qt::FramelessWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground);
    menu->setStyleSheet("QMenu {border-radius:5px;font-family:'Microsoft Yahei';font-size:14px;color:#fff;}"
                        " QMenu::item {height:30px; width:100px;padding-left:20px;border: 1px solid none;}"
                        "QMenu::item:selected {background-color:rgb(0,120,215);\
                        padding-left:20px;border: 1px solid rgb(65,173,255);}");

    m_profileBtn->setMenu(menu);
    ui->toolBar->addWidget(m_profileBtn);

    QLabel* space = new QLabel("      ",this);
    ui->toolBar->addWidget(space);

    // 初始化表
    for (int i = 0; i < tableSetting()->getTableHeaderData().length(); ++i){
        tableView()->setHeaderModel(i,tableSetting()->getTableHeaderData().at(i));
    }
    ui->tabWidget->addTab(tableView(),"原始数据表");
    auto computedWidget = ComputedPage::getInstance();

    ui->tabWidget->addTab(computedWidget,"计算结果页");
    ui->tabWidget->widget(1)->hide();
    auto clusterPage = ClusterPage::getInstance();

    ui->tabWidget->addTab(clusterPage,"聚类结果页");
    clusterPage->hide();
    auto statisticsPage = StatisticsPage::getInstance();

    ui->tabWidget->addTab(statisticsPage,"统计结果页");
    statisticsPage->hide();
    // 搜索
    connect(ui->mainStrokeCB,SIGNAL(currentTextChanged(QString)),this, SLOT(restStorkeType(QString)));
    auto tableSetting = TableSetting::getInstance();

    ui->mainGenderCB->addItems(QStringList() << "男" << "女");
    ui->mainLevelCB->addItems(tableSetting->getSportLevel());
    ui->mainTeamCB->addItems(tableSetting->getTeam());
    ui->mainStrokeCB->addItems(tableSetting->getStroke());
    ui->mainDistCB->addItems(tableSetting->getTestDintance());
    ui->mainEnvCB->addItems(tableSetting->getEnv());
    ui->mainStrageCB->addItems(tableSetting->getTrainStage());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    // TODO 自动保存
    int rowCount = tableView()->model()->rowCount();
    if(rowCount!=0){
        QString title = "是否保存表格数据";
        QString text = "警告，是否保存表格数据，请关闭之前操作";
        auto warnMessage = WarnMessage::getInstance();
        int ret = warnMessage->sendMessage(title,text);
        if (ret == QMessageBox::Yes){
            qDebug() << "保存";
        } else if (ret == QMessageBox::No){
            qDebug() <<"不保存";
        } else if (ret == QMessageBox::Cancel){
        }
    }
}

void MainWindow::setToolBarStatus()
{

}

void MainWindow::on_actAbout_triggered()
{
    Help::getInstance()->show();
}

void MainWindow::on_actMain_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actVisualization_triggered()
{
    ui->stackedWidget->addWidget(VisualizationPage());
    ui->stackedWidget->setCurrentWidget(VisualizationPage());
}

void MainWindow::on_actHistData_triggered()
{
    auto histDataPage = HistDataPage::getInstance();
    histDataPage->setQueryModel();
    ui->stackedWidget->addWidget(histDataPage);
    ui->stackedWidget->setCurrentWidget(histDataPage);
}

void MainWindow::on_actSetting_triggered()
{
    int ret = Settings()->exec();
    if(ret==QDialog::Rejected){

    } else if(ret==QDialog::Rejected){

    }
}

void MainWindow::on_mainSetting_clicked()
{
    if(ui->mainSettingPage->isHidden()){
        ui->mainSettingPage->show();
    } else{
        ui->mainSettingPage->hide();
    }
}

void MainWindow::actQuite_triggered()
{
    auto login = Login::getInstance();
    login->clearPassword();
    login->show();
    this->hide();
}

void MainWindow::actAccount_triggered()
{
    auto accountManager = AccountManager::getInstance();
    accountManager->exec();
}

void MainWindow::on_mainComputedBtn_clicked()
{
    ui->tabWidget->widget(1)->show();
    auto computedWidget = ComputedPage::getInstance();
    // 计算表
    tableView()->computedModel();
    // 更新数据库
    auto record = new DB::Record;
    for(int i=0; i<tableView()->model()->rowCount();i++){
        QString name = tableView()->model()->item(i,2)->text();
        QString birthday = tableView()->model()->item(i,0)->text().split("::").at(1);
        QString gender = tableView()->model()->item(i,3)->text();
        QString stroke = tableView()->model()->item(i,9)->text();
        QString type = tableView()->model()->item(i,10)->text();
        QString maxPower = tableView()->model()->item(i,15)->text();
        QString relPower = tableView()->model()->item(i,16)->text();
        QString percentage = tableView()->model()->item(i,17)->text();
        QString contribution_rate = tableView()->model()->item(i,18)->text();
        record->updateRecord(name,birthday,gender,stroke,type,maxPower,relPower,percentage,contribution_rate);
    }
    record->deleteLater();
    // 更新图表
    computedWidget->updateSinglePersonStatistics(tableView()->singlePersonStatistics());
    computedWidget->updatePersonStatistics(tableView()->personStatistics());
}

void MainWindow::on_mainClusterBtn_clicked()
{
    ui->tabWidget->widget(2)->show();
    ui->maxPowerCheckBox->isChecked();
    QMap<QString,bool> clusterItem = {
        {"maxPower", ui->maxPowerCheckBox->isChecked()},
        {"relPower", ui->relPowerCheckBox->isChecked()},
        {"percentage", ui->percentageCheckBox->isChecked()},
        {"contribution", ui->contributionCheckBox->isChecked()},
    };
    tableView()->setK(ui->kCB->currentText().toInt());
    tableView()->setIters(100);
    tableView()->setClusterItem(clusterItem);
    tableView()->clusterModel();
}

void MainWindow::on_mainStatisticsBtn_clicked()
{
    ui->tabWidget->widget(3)->show();
    auto statisticsPage = StatisticsPage::getInstance();
    tableView()->statisticsModel();
    ui->tabWidget->setCurrentWidget(statisticsPage);
}


void MainWindow::on_mainAsSaveBtn_clicked()
{
    Player()->saveModelXlsx();
}


void MainWindow::on_mainOpenExcelBtn_clicked()
{
    ThreadPool* threadPool = ThreadPool::getInstance();
    QVector<QStringList> tableDatas = Player()->openXlsx();
    emit sendTableDatas(tableDatas);

    LoadTableDataRunable* loadTableDataRunable = new LoadTableDataRunable;
    threadPool->submitTask(loadTableDataRunable);
}


void MainWindow::on_mainTemplateBtn_clicked()
{
    Player()->exportTemplate(tableSetting()->getTableHeaderData());
}

void MainWindow::on_appendData_clicked()
{
    if(ui->tabWidget->currentWidget()!=ui->tabWidget->widget(0)){
        ui->tabWidget->setCurrentIndex(0);
    }

    auto newData = NewData::getInstance();
    auto computedPage = ComputedPage::getInstance();
    newData->clearText();
    int ret = newData->exec();
    if (ret == QDialog::Accepted) {
        QList<QStandardItem*> aItemList = newData->getRowData(tableView()->historyRowCount());
        bool isRequired = newData->isRequired(aItemList);
        bool isExistsData = tableView()->isExistsRecord(newData->uniqueData());
        if(!isRequired){
            this->on_appendData_clicked();
        } else if(isExistsData) {
            newData->setWarnText("表中已存在同项数据");
            this->on_appendData_clicked();
        } else {
            // 同步到数据库
            DB::Person* person_db = new DB::Person();
            DB::Record* record_db = new DB::Record();
            QString name = aItemList.at(2)->text();
            QString gender = aItemList.at(3)->text();
            QString birthday = aItemList.at(0)->text().split("::").at(1);
            QString person = name + "-" +gender + "-" + birthday;
            person_db->createPerson(aItemList.at(2)->text(),aItemList.at(0)->text().split("::").at(1),aItemList.at(3)->text(),aItemList.at(4)->text());
            record_db->createRecord(aItemList.at(2)->text(),aItemList.at(0)->text().split("::").at(1),aItemList.at(3)->text(),
                                 aItemList.at(6)->text(),aItemList.at(7)->text(),aItemList.at(8)->text(),aItemList.at(9)->text(),
                                 aItemList.at(10)->text(),aItemList.at(11)->text(),aItemList.at(12)->text(),aItemList.at(13)->text(),
                                 aItemList.at(14)->text(),aItemList.at(19)->text(),aItemList.at(1)->text().split("::").at(1));
            // 创建chart
            if(!tableView()->isExistsPerson(person)){
                computedPage->createSinglePersonChart(person);
            }
            // 添加数据到表格
            tableView()->addRowData(aItemList);
            QVector<double> values ={aItemList.at(12)->text().toDouble(),aItemList.at(13)->text().toDouble(),
                                     aItemList.at(14)->text().toDouble(),0,0,0,0};
            tableView()->addTableData(person,aItemList.at(4)->text(),aItemList.at(9)->text(),aItemList.at(10)->text(),aItemList.at(11)->text(),values);
            tableView()->setColumnHidden(tableSetting()->getTableHeaderData().length(), true);
            person_db->deleteLater();
            record_db->deleteLater();
        }
        // 刷新主页面表格
        this->on_mainRefresh_clicked();
    }
}

void MainWindow::on_mainViewBtn_clicked()
{
    auto view = ViewPage::getInstance();
    view->createShowMessage(tableView()->selectRowIndexs());
    view->exec();
}


void MainWindow::on_mainExportBtn_clicked()
{
    Player()->saveXlsx();
}

void MainWindow::on_mainAllDeleteBtn_clicked()
{
    QVector<int> rowIndexs = tableView()->selectRowIndexs();
    // 删除数据库中数据
    auto record = new DB::Record;
    record->deleteRecord(rowIndexs);
    // 删除表、图数据
    std::sort(rowIndexs.rbegin(),rowIndexs.rend()); // 逆序删除
    for(int i=0; i< rowIndexs.size(); i++){
        QString name = tableView()->model()->index(rowIndexs.at(i),2).data().toString();
        QString gender = tableView()->model()->index(rowIndexs.at(i),3).data().toString();
        QString birthday = tableView()->model()->index(rowIndexs.at(i),0).data().toString().split("::").at(1);
        QString person = name + "-" + gender + "-" + birthday;
        tableView()->delTableData(person,tableView()->model()->index(rowIndexs.at(i),9).data().toString(),
                                  tableView()->model()->index(rowIndexs.at(i),10).data().toString(),
                                  tableView()->model()->index(rowIndexs.at(i),11).data().toString());
        tableView()->model()->removeRow(rowIndexs.at(i));
        if(!tableView()->isExistsPerson(person)){
            tableView()->delTableData(person);
            auto computedPage = ComputedPage::getInstance();
            computedPage->deleteSinglePersonChart(person);
        }
    }
}

void MainWindow::on_mainSearch_clicked()
{


    auto tableView = TableView::getInstance();
    tableView->proxyModel()->setRefresh(""); // 不可删除
    tableView->setColumnHidden(tableSetting()->getTableHeaderData().length(), false);

    if(m_nameSearch!=""){
        tableView->proxyModel()->setSourceModel(tableView->model());
        tableView->proxyModel()->setFilterRegExp(m_nameSearch);
    }

    tableView->proxyModel()->setRxCol3(ui->mainGenderCB->currentText());
    tableView->proxyModel()->setSourceModel(tableView->model());
    tableView->proxyModel()->setFilterRegExp(ui->mainGenderCB->currentText());

    tableView->proxyModel()->setRxCol4(ui->mainWeightSB->text());
    tableView->proxyModel()->setSourceModel(tableView->model());
    tableView->proxyModel()->setFilterRegExp(ui->mainWeightSB->text());

    tableView->proxyModel()->setRxCol6(ui->mainLevelCB->currentText());
    tableView->proxyModel()->setSourceModel(tableView->model());
    tableView->proxyModel()->setFilterRegExp(ui->mainLevelCB->currentText());

    tableView->proxyModel()->setRxCol7(ui->mainTeamCB->currentText());
    tableView->proxyModel()->setSourceModel(tableView->model());
    tableView->proxyModel()->setFilterRegExp(ui->mainTeamCB->currentText());

    tableView->proxyModel()->setRxCol8(ui->mainStrageCB->currentText());
    tableView->proxyModel()->setSourceModel(tableView->model());
    tableView->proxyModel()->setFilterRegExp(ui->mainStrageCB->currentText());

    tableView->proxyModel()->setRxCol9(ui->mainStrokeCB->currentText());
    tableView->proxyModel()->setSourceModel(tableView->model());
    tableView->proxyModel()->setFilterRegExp(ui->mainStrokeCB->currentText());

    tableView->proxyModel()->setRxCol10(ui->mainTypeCB->currentText());
    tableView->proxyModel()->setSourceModel(tableView->model());
    tableView->proxyModel()->setFilterRegExp(ui->mainTypeCB->currentText());


    tableView->proxyModel()->setRxCol11(ui->mainDistCB->currentText());
    tableView->proxyModel()->setSourceModel(tableView->model());
    tableView->proxyModel()->setFilterRegExp(ui->mainDistCB->currentText());


    tableView->proxyModel()->setRxCol19(ui->mainEnvCB->currentText());
    tableView->proxyModel()->setSourceModel(tableView->model());
    tableView->proxyModel()->setFilterRegExp(ui->mainEnvCB->currentText());
}

void MainWindow::on_mainRefresh_clicked()
{
    if(ui->tabWidget->currentWidget()!=ui->tabWidget->widget(0)){
        ui->tabWidget->setCurrentIndex(0);
    }
    tableView()->setColumnHidden(tableSetting()->getTableHeaderData().length(), true);
    tableView()->proxyModel()->setRefresh("source");
    tableView()->proxyModel()->setFilterRegExp("source");
}

void MainWindow::setUserName(QString text, bool userType)
{
    if (userType){
        m_userPixmap.load(":/images/images/system.png");
        m_profileBtn->setStyleSheet("QPushButton{border:0px;}");
        m_profileBtn->setIcon(m_userPixmap);
        m_profileBtn->setIconSize(m_userPixmap.size());
        m_profileBtn->resize(m_userPixmap.size());
    } else {
        m_userPixmap.load(":/images/images/user.png");
        m_profileBtn->setStyleSheet("QPushButton{border:0px;}");
        m_profileBtn->setIcon(m_userPixmap);
        m_profileBtn->setIconSize(m_userPixmap.size());
        m_profileBtn->resize(m_userPixmap.size());
    }
    m_username->setText(text);
}

void MainWindow::nameSearch(QString text)
{
    m_nameSearch = text;
}

void MainWindow::restStorkeType(const QString &text)
{
    auto tableSetting = TableSetting::getInstance();
    if (text != "请选择") {
        ui->mainTypeCB->clear();
        QStringList strokeItem = tableSetting->getStrokeItem()[text];
        qDebug() << text<< strokeItem;
        ui->mainTypeCB->addItems(strokeItem);
    }
}

void MainWindow::setKValue()
{
    ui->kCB->clear();

    int size = tableView()->searchRowIndexs().size();
    if (size>=3){
        int max;
        if (size + 1<=11){
            max =size + 1;
        } else {
            max = 11;
        }
        for(int i=3; i< max; i++){
            ui->kCB->addItem(QString::number(i));
        }
        ui->kCB->setCurrentIndex(0);
    } else {
        for(int i=0; i<size; i++){
            ui->kCB->addItem(QString::number(i+1));
        }
        ui->kCB->setCurrentIndex(size-1);
    }
}



TableSetting* MainWindow::tableSetting()
{
    return TableSetting::getInstance();
}

TableView* MainWindow::tableView()
{
    return TableView::getInstance();
}

Player* MainWindow::Player()
{
    return Player::getInstance();
}

Settings* MainWindow::Settings()
{
    return Settings::getInstance();
}

VisualizationPage* MainWindow::VisualizationPage()
{
    return VisualizationPage::getInstance();
}

void MainWindow::on_scorePushButton_clicked()
{
    auto score = Score::getInstance();
    QVector<QVector<QString>> scoreDatas = Player()->openScoreXlsx();
    score->setScoreCommonStandard(scoreDatas);
}

