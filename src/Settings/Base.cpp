#include "Base.h"
#include <QDebug>
#include <QCoreApplication>

Base::Base()
{
//    this->readSettings();
//    this->writeSettings();
//    this->_userSettings();
}


void Base::_userSettings()
{
    m_userSettings = new QSettings(":/config/config/Basic.ini",QSettings::IniFormat);
    m_userSettings->beginGroup("Table");
    m_userSettings->setValue("header","11111");
    m_userSettings->endGroup();
}

void Base::readSettings()
{
     QString fileName = QCoreApplication::applicationDirPath() + "/bin/config/Basic.ini";
     m_userSettings = new QSettings(fileName,QSettings::IniFormat);
     m_userSettings->setIniCodec(QTextCodec::codecForName("UTF-8"));
     m_userSettings->beginGroup("Table");
     QString size = m_userSettings->value("headerdata","null").toString();
     QString size2 = m_userSettings->value("genderIndex","null").toString();
     qDebug() << size<<size2;
     m_userSettings->endGroup();
}

void Base::writeSettings()
{
    QSettings* config =  new QSettings("/Users/guozeping/Downloads/Swimming/config/Basic.ini",QSettings::IniFormat);
    config->beginGroup("Table");
    config->setValue("headerdata","22222");
    config->endGroup();
    delete config;
}
