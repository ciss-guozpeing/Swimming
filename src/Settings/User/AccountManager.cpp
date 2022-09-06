#include "AccountManager.h"
#include "ui_AccountManager.h"

#include "src/DB/User.h"
#include <QDebug>
static AccountManager* INSTANCE=nullptr;

AccountManager::AccountManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountManager)
{
    ui->setupUi(this);
    this->setWindowTitle("开通账户");
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确定");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
    ui->buttonBox->button(QDialogButtonBox::Apply)->setText("应用");

    // TODO 设置校验
//    QValidator
//    ui->passwordLineEdit->setValidator();
//    ui->usernameLineEdit->setValidator();
}

AccountManager::~AccountManager()
{
    delete ui;
}

AccountManager *AccountManager::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new AccountManager();
    }
    return INSTANCE;
}
void AccountManager::setIsApply(bool isApply)
{
    m_isApply = isApply;
}
bool AccountManager::isApply()
{
    return m_isApply;
}

void AccountManager::on_buttonBox_clicked(QAbstractButton *button)
{
    auto user = new DB::User();
    QString password = ui->passwordLineEdit->text();
    QString username = ui->usernameLineEdit->text();
    bool isSupper = ui->isSupperCheckBox->isChecked();
    if(button->text() == "确定"){
        if(isApply()){
            this->hide();
            this->setIsApply(false);
        } else{
            if(isSupper){
                user->createSupperUser(username,password);
            } else{
                user->createUser(username,password);
            }
            ui->passwordLineEdit->clear();
            ui->usernameLineEdit->clear();
            ui->isSupperCheckBox->setCheckState(Qt::Unchecked);
            this->hide();
        }
    }

    if(button->text() == "应用"){
        if(isSupper){
            user->createSupperUser(username,password);
        } else{
            user->createUser(username,password);
        }
        this->setIsApply(true);
    }

    if(button->text() == "取消"){
        ui->passwordLineEdit->clear();
        ui->usernameLineEdit->clear();
        ui->isSupperCheckBox->setCheckState(Qt::Unchecked);
        this->hide();
    }

    user->deleteLater();
}


