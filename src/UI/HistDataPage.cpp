#include "HistDataPage.h"
#include "ui_HistDataPage.h"

#include "src/UI/Login.h"
static HistDataPage* INSTANCE=nullptr;
HistDataPage::HistDataPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistDataPage)
{
    ui->setupUi(this);
    auto baseDB = new DB::Base;
    auto db = baseDB->driver();
    db.open();
    m_personModel = new QSqlTableModel(this, db);
    m_userModel = new QSqlTableModel(this, db);
    m_queryModel = new QSqlQueryModel(this);
    db.close();
    // 超级用户启用
    ui->userBtn->setVisible(Login::getInstance()->userType());
}

HistDataPage::~HistDataPage()
{
    delete ui;
}

HistDataPage *HistDataPage::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new HistDataPage();
    }
    return INSTANCE;
}

QSqlTableModel* HistDataPage::personModel()
{
    return m_personModel;
}

QSqlTableModel* HistDataPage::userModel()
{
    return m_userModel;
}

QSqlQueryModel* HistDataPage::queryModel()
{
    return m_queryModel;
}
void HistDataPage::setPersonModel()
{
    auto db = new DB::Base();
    db->open();
    m_personModel->setTable("person");
    m_personModel->select();
    m_personModel->setHeaderData(0,Qt::Horizontal,"序号");
    m_personModel->setHeaderData(1,Qt::Horizontal,"姓名");
    m_personModel->setHeaderData(2,Qt::Horizontal,"出生日期");
    m_personModel->setHeaderData(3,Qt::Horizontal,"性别");
    m_personModel->setHeaderData(4,Qt::Horizontal,"体重");
    ui->personTableView->setModel(m_personModel);
    ui->personTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->personTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}
void HistDataPage::setUserModel()
{
    auto db = new DB::Base();
    db->open();
    m_userModel->setTable("user");
    m_userModel->select();
    m_userModel->setHeaderData(0,Qt::Horizontal,"序号");
    m_userModel->setHeaderData(1,Qt::Horizontal,"用户名");
    m_userModel->setHeaderData(2,Qt::Horizontal,"密码");
    m_userModel->setHeaderData(3,Qt::Horizontal,"超级用户");
    m_userModel->setHeaderData(4,Qt::Horizontal,"电子邮件");
    ui->userTableView->setModel(m_userModel);
    ui->userTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->userTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}
void HistDataPage::setQueryModel()
{
    auto db = new DB::Base();
    db->open();
    m_queryModel->setQuery("SELECT person_id,create_at,name,birthday,gender,weight,level,team,stage,stroke,type,distance,maxpower1,"
                           "maxpower2, maxpower3,maxpower,relpower,percentage,contribution_rate,environment from record LEFT JOIN person on record.person_id == person.id");


    QStringList header;
    header << "序号" <<"创建时间"<< "姓名" << "出生日期" << "性别" << "体重" << "运动等级" << "所属队伍"
           << "训练阶段" << "泳姿" << "类别" << "测试距离" << "最大力1" << "最大力2" << "最大力3"
           << "最大力" << "相对力" << "百分比%" << "贡献率" << "环境";
    for(int i=0; i<header.length();i++){
        m_queryModel->setHeaderData(i,Qt::Horizontal,header.at(i));
    }

    //设置模型
    ui->recordTableView->setModel(m_queryModel);
    ui->recordTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->recordTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}


void HistDataPage::on_recordBtn_clicked()
{
    this->setQueryModel();
    ui->stackedWidget->setCurrentWidget(ui->page_1);
}


void HistDataPage::on_personBtn_clicked()
{
    this->setPersonModel();
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void HistDataPage::on_userBtn_clicked()
{
    this->setUserModel();
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

