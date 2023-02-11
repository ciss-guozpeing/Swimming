#include "TableSetting.h"
#include "src/Settings/Base.h"
#include <QDebug>
#include <QApplication>
#include <QDir>
static TableSetting* INSTANCE=nullptr;

TableSetting::TableSetting()
{
    QString fileName;
    #ifdef Q_OS_WIN
        qDebug() << "win";
    #endif
    #ifdef Q_OS_MAC
        fileName = fileName = QCoreApplication::applicationDirPath() + "/../../../config/Basic.ini";
    #endif
    #ifdef Q_OS_LINUX
        qDebug()<<"linux";
    #endif
    m_tableSetting = new QSettings(fileName,QSettings::IniFormat);
    m_tableSetting->setIniCodec(QTextCodec::codecForName("UTF-8"));
}

TableSetting::~TableSetting()
{
    delete this;
}

TableSetting *TableSetting::getInstance()
{
    if (!INSTANCE) {
        INSTANCE = new TableSetting();
    }
    return INSTANCE;
}

QStringList TableSetting::getTableHeaderData()
{
    QStringList headerData;
    m_tableSetting->beginGroup("Table");
    m_tableSetting->setIniCodec(QTextCodec::codecForName("UTF-8"));
    QString s_headerData = m_tableSetting->value("headerdata","null").toString();
    headerData = s_headerData.split(",");
    m_tableSetting->endGroup();
    return headerData;
}

QStringList TableSetting::getSportLevel() const
{
    QStringList sportLevel;
    m_tableSetting->beginGroup("SportLevel");
    QString s_sportLevel = m_tableSetting->value("sportlevel","null").toString();
    sportLevel = s_sportLevel.split(",");
    m_tableSetting->endGroup();
    return sportLevel;
}
QStringList TableSetting::getEnv() const
{
    QStringList env;
    m_tableSetting->beginGroup("Env");
    QString s_env = m_tableSetting->value("env","null").toString();
    env = s_env.split(",");
    m_tableSetting->endGroup();
    return env;
}
QStringList TableSetting::getTestDintance() const
{
    QStringList testDintance;
    m_tableSetting->beginGroup("TestDintance");
    QString s_testDintancel = m_tableSetting->value("testdistance","null").toString();
    testDintance = s_testDintancel.split(",");
    m_tableSetting->endGroup();
    return testDintance;
}
QStringList TableSetting::getTeam() const
{
    QStringList team;
    m_tableSetting->beginGroup("Team");
    QString s_team = m_tableSetting->value("team","null").toString();
    team = s_team.split(",");
    m_tableSetting->endGroup();
    return team;
}
QStringList TableSetting::getTrainStage() const
{
    QStringList trainStage;
    m_tableSetting->beginGroup("TrainStage");
    QString s_sportLevel = m_tableSetting->value("trainstage","null").toString();
    trainStage = s_sportLevel.split(",");
    m_tableSetting->endGroup();
    return trainStage;
}


const QMap<QString,int> TableSetting::getHeaderIndex() const
{
    QMap<QString,int> headerIndex;
    QStringList headerIndexKeys;
    m_tableSetting->beginGroup("HeaderIndex");
    headerIndexKeys = m_tableSetting->allKeys();
    for (int i=0; i<headerIndexKeys.length(); i++) {
        headerIndex.insert(headerIndexKeys[i],m_tableSetting->value(headerIndexKeys[i],"null").toString().toInt());
    }
    m_tableSetting->endGroup();
    return headerIndex;
}


const QStringList TableSetting::getStroke() const
{
    QStringList stroke;
    QStringList strokeKeys;
    m_tableSetting->beginGroup("Stroke");
    strokeKeys = m_tableSetting->allKeys();
    for (int i=0; i<strokeKeys.length(); i++) {
        stroke.push_back(m_tableSetting->value(strokeKeys[i],"null").toString());
    }
    m_tableSetting->endGroup();
    return stroke;
}

const QMap<QString,QStringList> TableSetting::getStrokeItem() const
{
    QMap<QString,QStringList> strokeItem;
    QStringList strokeKeys;
    QStringList strokeValues;
    m_tableSetting->beginGroup("Stroke");
    strokeKeys = m_tableSetting->allKeys();
    for (int i=0; i<strokeKeys.length(); i++) {
        strokeValues.push_back(m_tableSetting->value(strokeKeys[i],"null").toString());
    }
    m_tableSetting->endGroup();

    m_tableSetting->beginGroup("StrokeItem");
    for (int i=0; i<strokeKeys.length(); i++) {
        QString item = m_tableSetting->value(strokeKeys[i] + "_item","null").toString();
        QStringList sl_item = item.split(",");
        strokeItem.insert(strokeValues[i],sl_item);
    }
    m_tableSetting->endGroup();
    return strokeItem;
}

QStringList TableSetting::getStatisticalRowHeader() const
{
    QStringList statisticalHeader;
    m_tableSetting->beginGroup("StatisticalHeader");
    QString value =  m_tableSetting->value("statistical_header","null").toString();
    statisticalHeader = value.split(",");
    m_tableSetting->endGroup();
    return statisticalHeader;
}

QStringList TableSetting::getStaticticalColHeader() const
{
    QStringList statisticalRowHeader;
    m_tableSetting->beginGroup("StatisticalRowHeader");
    QString value =  m_tableSetting->value("statistical_rowheader","null").toString();
    statisticalRowHeader = value.split(",");
    m_tableSetting->endGroup();
    return statisticalRowHeader;
}
