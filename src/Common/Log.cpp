#include "log4qt/log4qt.h"
#include "log4qt/propertyconfigurator.h"

#include "src/Common/Log.h"
#include "src/Common/Notice/Notification/ZpNotificationManager.h"

Log * Log::_pInstance = 0;
QMutex Log::_mutex;
Log4Qt::Logger * Log::_pLoggerDebug = 0;
Log4Qt::Logger * Log::_pLoggerInfo = 0;
Log4Qt::Logger * Log::_pLoggerWarn = 0;
Log4Qt::Logger * Log::_pLoggerError = 0;
QString Log::_configFilePath;

Log::Log(QObject *parent) : QObject(parent)
{
    // 一定要配置文件，不然运行起来会直接当掉
    Log4Qt::BasicConfigurator::configure();
}

Log *Log::instance()
{
    if(!_pInstance)
    {
        QMutexLocker mutexLocker(&_mutex);
        if(!_pInstance)
        {
            Log *pInstance = new Log();
            _pInstance = pInstance;
        }
    }
    return _pInstance;
}

void Log::init(QString configFilePath)
{
    _configFilePath = configFilePath;
     Log4Qt::PropertyConfigurator::configure(_configFilePath);
    _pLoggerDebug = Log4Qt::Logger::logger("debug");
    _pLoggerInfo = Log4Qt::Logger::logger("info");
    _pLoggerWarn = Log4Qt::Logger::logger("warn");
    _pLoggerError = Log4Qt::Logger::logger("error");
}

void Log::debug(QString msg)
{
    _pLoggerDebug->debug(msg);
}

void Log::info(QString msg)
{
    _pLoggerInfo->info(msg);
}

void Log::warn(QString msg)
{
    _pLoggerWarn->warn(msg);
}

void Log::error(QString msg)
{
    _pLoggerError->error(msg);
}

void Log::sendLogMessage(LOGGERTYPE loggerType,QString title, QString text, bool isSyncNotify)
{
    auto zpNotificationManager = ZpNotificationManager::getInstance();

    switch (loggerType){
    case LOGGERTYPE::DEBUG:
        LOG_DEBUG(QString("%1-%2").arg(title,text));
        break;
    case LOGGERTYPE::INFO:
        LOG_DEBUG(QString("%1-%2").arg(title,text));
        if(isSyncNotify){
            zpNotificationManager->notify(title,text,":/images/images/success.png","");
        }
        break;
    case LOGGERTYPE::WARN:
        LOG_DEBUG(QString("%1-%2").arg(title,text));
        if(isSyncNotify){
            zpNotificationManager->notify(title,text,":/images/images/warn.png","");
        }
        break;
    case LOGGERTYPE::ERROR:
        break;
        LOG_DEBUG(QString("%1-%2").arg(title,text));
        if(isSyncNotify){
            zpNotificationManager->notify(title,text,":/images/images/failed.png","");
        }
    default:
        break;
    }
}

void Log::sendNotify(LOGGERTYPE loggerType, QString title, QString text)
{
    auto zpNotificationManager = ZpNotificationManager::getInstance();

    switch (loggerType){
    case LOGGERTYPE::DEBUG:
        break;
    case LOGGERTYPE::INFO:
        zpNotificationManager->notify(title,text,":/images/images/success.png","");
        break;
    case LOGGERTYPE::WARN:
        zpNotificationManager->notify(title,text,":/images/images/warn.png","");
        break;
    case LOGGERTYPE::ERROR:
        zpNotificationManager->notify(title,text,":/images/images/failed.png","");
        break;
    default:
        break;
    }
}
