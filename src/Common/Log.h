#include <QObject>
#include <QMutex>
#include <QMutexLocker>
#include <QCoreApplication>

#include "log4qt/logger.h"
#include "log4qt/basicconfigurator.h"

#define LOG_DEBUG(msg) Log::instance()->debug(QString("[%1] Message:%2").arg(QString("FILE:%1  LINE:%2  FUNC:%3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__)).arg(msg));

#define LOG_INFO(msg) Log::instance()->info(QString("[%1] Message:%2").arg(QString("FILE:%1  LINE:%2  FUNC:%3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__)).arg(msg));

#define LOG_WARN(msg) Log::instance()->warn(QString("[%1] Message:%2").arg(QString("FILE:%1  LINE:%2  FUNC:%3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__)).arg(msg));

#define LOG_ERROR(msg) Log::instance()->error(QString("[%1] Message:%2").arg(QString("FILE:%1  LINE:%2  FUNC:%3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__)).arg(msg));

// 以类名对象形式记录信息
#define LOG_OBJECT_DEBUG(msg) Log::instance()->debug(QString("[%1]%2").arg(QString("%1::%2:%3").arg(this->metaObject()->className()).arg(__FUNCTION__).arg(__LINE__)).arg(msg));

#define LOG_OBJECT_INFO(msg) Log::instance()->info(msg);

#define LOG_OBJECT_WARN(msg) Log::instance()->warn(msg);

#define LOG_OBJECT_ERROR(msg) Log::instance()->error(msg);

class Log : public QObject
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER
public:
    explicit Log(QObject *parent = nullptr);
    enum LOGGERTYPE{
        INFO,
        DEBUG,
        WARN,
        ERROR
    };
    void sendLogMessage(LOGGERTYPE loggerType,QString title, QString text, bool isSyncNotify);
    void sendNotify(LOGGERTYPE loggerType, QString title, QString text);
    Q_ENUM(LOGGERTYPE);
signals:

public slots:
    static Log * instance();

public slots:
    void init(QString configFilePath);

public slots:
    void debug(QString msg);
    void info(QString msg);
    void warn(QString msg);
    void error(QString msg);

private:
    static Log *_pInstance;
    static QMutex _mutex;
    static Log4Qt::Logger * _pLoggerDebug;
    static Log4Qt::Logger * _pLoggerInfo;
    static Log4Qt::Logger * _pLoggerWarn;
    static Log4Qt::Logger * _pLoggerError;
    static QString _configFilePath;

};
