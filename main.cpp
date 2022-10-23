#include <QApplication>
#include <QtCore>
#include <QTextCodec>
#include <QThread>

#include "mainwindow.h"
#include "src/AppInfo.h"
#include "src/Common/Log.h"
#include "src/Common/ModuleManager.h"
#include "src/DB/BaseDB.h"
#include "src/DB/User.h"
#include "src/DB/DBPool.h"
#include "src/UI/Login.h"
#include "src/Settings/WindowSetting.h"
#include "src/Common/ReturnData.h"

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    qApp->setOrganizationName(APP_Organization);
    qApp->setApplicationName(APP_NAME);
    qApp->setApplicationVersion(APP_VERSION);
    qApp->setApplicationDisplayName(APP_NAME);
    MainWindow w;
    Login* login = Login::getInstance();
    //
    qRegisterMetaType<ReturnData>("ReturnData");
    // 初始化数据库
     auto dbPool = ConnectionPool::openConnection();

    // 配置日志
    QThread::currentThread()->setObjectName("主线程");
    Log::instance()->init(QCoreApplication::applicationDirPath() + "/" +"config/log.conf");
    LOG_INFO(QString(" '%1' 程序开启").arg(qApp->applicationName()));


    // 初始化模块管理类
    auto moduleManager = ModuleManager::getInstance();
    moduleManager->initModuleInstance();

    // 配置主题
    WindowSetting* w_setting =  WindowSetting::getInstance();
    w_setting->configureDarkUi();
    //创建默认超级用户
    DB::User* user = new DB::User();
    if(!w_setting->isExistsSupperUser()){
        user->createDefaultSupperUser();
        w_setting->setSupperUser();
    }
    user->deleteLater();

    // 展示
    if (login->exec() == QDialog::Accepted){
        return a.exec();
    } else{
        return 0;
    }
}
