#include "ViewBase.h"
#include "ui_ViewBase.h"

ViewBase::ViewBase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewBase)
{
    ui->setupUi(this);
}

ViewBase::~ViewBase()
{
    delete ui;
}

void ViewBase::setText(QVector<QString> rowData)
{
    ui->LineEdit_1->setText(rowData.at(0));
    ui->LineEdit_2->setText(rowData.at(1));
    ui->LineEdit_3->setText(rowData.at(2));
    ui->LineEdit_4->setText(rowData.at(3));
    ui->LineEdit_5->setText(rowData.at(4));
    ui->LineEdit_6->setText(rowData.at(5));
    ui->LineEdit_7->setText(rowData.at(6));
    ui->LineEdit_8->setText(rowData.at(7));
    ui->LineEdit_9->setText(rowData.at(8));
    ui->LineEdit_10->setText(rowData.at(9));
    ui->LineEdit_11->setText(rowData.at(10));
    ui->LineEdit_12->setText(rowData.at(11));
    ui->LineEdit_13->setText(rowData.at(12));
    ui->LineEdit_14->setText(rowData.at(13));
    ui->LineEdit_15->setText(rowData.at(14));
    ui->LineEdit_16->setText(rowData.at(15));
    ui->LineEdit_17->setText(rowData.at(16));
    ui->LineEdit_18->setText(rowData.at(17));
    ui->LineEdit_19->setText(rowData.at(18));
    ui->LineEdit_20->setText(rowData.at(19));
}
