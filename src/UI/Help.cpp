#include "Help.h"
#include "ui_Help.h"
#include <QIcon>

static Help* INSTANCE=nullptr;
Help::Help(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/images/images/swimming.png"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
}

Help::~Help()
{
    if (INSTANCE!=NULL)
    {
        delete  INSTANCE ;
        INSTANCE =  NULL;
    }
    delete ui;
}

Help* Help::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new Help();
    }
    return INSTANCE;
}
