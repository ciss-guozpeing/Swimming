#include "Settings.h"
#include "ui_settings.h"

#include <QDebug>
static Settings* INSTANCE=nullptr;
Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确定");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
    ui->buttonBox->button(QDialogButtonBox::Apply)->setText("应用");
}

Settings::~Settings()
{
    delete ui;
}

Settings *Settings::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Settings();
    }
    return INSTANCE;
}

void Settings::on_buttonBox_accepted()
{
    this->show();
}


void Settings::on_buttonBox_rejected()
{
    this->hide();
}

