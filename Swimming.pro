QT       += core gui
QT       += datavisualization
QT       += sql
QT       += websockets
QT       += charts
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG(release, debug|release){#仅在release模式下，才以管理员权限运行
    RC_FILE=manifest.rc
}

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#-----------------------------------------------------------------------------------------
# Libraries
#-----------------------------------------------------------------------------------------

include(libs/Libraries.pri)

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/Algorithm/Kmeans.cpp \
    src/Algorithm/Score.cpp \
    src/Algorithm/Statistics.cpp \
    src/Common/Log.cpp \
    src/Common/Notice/Notification/ZpNotification.cpp \
    src/Common/Notice/Notification/ZpNotificationManager.cpp \
    src/Common/BasicTool.cpp \
    src/Common/Message.cpp \
    src/Common/ModuleManager.cpp \
    src/Common/ThreadPool.cpp \
    src/Common/window.cpp \
    src/DB/BaseDB.cpp \
    src/DB/DBPool.cpp \
    src/DB/Person.cpp \
    src/DB/Record.cpp \
    src/DB/User.cpp \
    src/Excel/Player.cpp \
    src/Excel/Save.cpp \
    src/Settings/Base.cpp \
    src/Settings/Settings.cpp \
    src/Settings/TableSetting.cpp \
    src/Settings/User/AccountManager.cpp \
    src/Settings/WindowSetting.cpp \
    src/Tasks/LoadTableData.cpp \
    src/UI/ClusterPage.cpp \
    src/UI/ComputedPage.cpp \
    src/UI/Help.cpp \
    src/UI/HistDataPage.cpp \
    src/UI/Login.cpp \
    src/UI/NewData.cpp \
    src/UI/SqlDelegate/SqlQueryModel.cpp \
    src/UI/StatisticsPage.cpp \
    src/UI/TableDelegate/AgeDelegate.cpp \
    src/UI/TableDelegate/DistanceDelegate.cpp \
    src/UI/TableDelegate/EnvDelegate.cpp \
    src/UI/TableDelegate/FlowLayout.cpp \
    src/UI/TableDelegate/GenderDelegate.cpp \
    src/UI/TableDelegate/LevelDelegate.cpp \
    src/UI/TableDelegate/MaxPowerDelegate.cpp \
    src/UI/TableDelegate/ReadonlyDelegate.cpp \
    src/UI/TableDelegate/SortFilterProxyModel.cpp \
    src/UI/TableDelegate/StrokeDelegate.cpp \
    src/UI/TableDelegate/StrokeItemDelegate.cpp \
    src/UI/TableDelegate/TableData.cpp \
    src/UI/TableDelegate/TeamDelegate.cpp \
    src/UI/TableDelegate/TrainStageDelegate.cpp \
    src/UI/TableDelegate/ViewBase.cpp \
    src/UI/TableDelegate/WeightDelegate.cpp \
    src/UI/TableView.cpp \
    src/UI/ViewPage.cpp \
    src/UI/Visualization/VisualizationPage.cpp \


HEADERS += \
    mainwindow.h \
    src/Algorithm/Kmeans.h \
    src/Algorithm/Score.h \
    src/Algorithm/Statistics.h \
    src/AppInfo.h \
    src/Common/Notice/Notification/ZpNotification.h \
    src/Common/Notice/Notification/ZpNotificationManager.h \
    src/Common/BasicTool.h \
    src/Common/Log.h \
    src/Common/Message.h \
    src/Common/ModuleManager.h \
    src/Common/ReturnData.h \
    src/Common/ThreadPool.h \
    src/Common/window.h \
    src/DB/BaseDB.h \
    src/DB/DBPool.h \
    src/DB/Person.h \
    src/DB/Record.h \
    src/DB/User.h \
    src/Excel/Player.h \
    src/Excel/Save.h \
    src/Settings/Base.h \
    src/Settings/Settings.h \
    src/Settings/TableSetting.h \
    src/Settings/User/AccountManager.h \
    src/Settings/WindowSetting.h \
    src/Tasks/LoadTableData.h \
    src/UI/ClusterPage.h \
    src/UI/ComputedPage.h \
    src/UI/Help.h \
    src/UI/HistDataPage.h \
    src/UI/Login.h \
    src/UI/NewData.h \
    src/UI/SqlDelegate/SqlQueryModel.h \
    src/UI/StatisticsPage.h \
    src/UI/TableDelegate/AgeDelegate.h \
    src/UI/TableDelegate/DistanceDelegate.h \
    src/UI/TableDelegate/EnvDelegate.h \
    src/UI/TableDelegate/FlowLayout.h \
    src/UI/TableDelegate/GenderDelegate.h \
    src/UI/TableDelegate/LevelDelegate.h \
    src/UI/TableDelegate/MaxPowerDelegate.h \
    src/UI/TableDelegate/ReadonlyDelegate.h \
    src/UI/TableDelegate/SortFilterProxyModel.h \
    src/UI/TableDelegate/StrokeDelegate.h \
    src/UI/TableDelegate/StrokeItemDelegate.h \
    src/UI/TableDelegate/TableData.h \
    src/UI/TableDelegate/TeamDelegate.h \
    src/UI/TableDelegate/TrainStageDelegate.h \
    src/UI/TableDelegate/ViewBase.h \
    src/UI/TableDelegate/WeightDelegate.h \
    src/UI/TableView.h \
    src/UI/ViewPage.h \
    src/UI/Visualization/VisualizationPage.h \

FORMS += \
    mainwindow.ui \
    src/Settings/User/AccountManager.ui \
    src/Settings/settings.ui \
    src/UI/Help.ui \
    src/UI/HistDataPage.ui \
    src/UI/TableDelegate/ViewBase.ui \
    src/UI/Visualization/VisualizationPage.ui \
    src/UI/clusterpage.ui \
    src/UI/computedpage.ui \
    src/UI/login.ui \
    src/UI/newdata.ui \
    src/UI/statisticspage.ui \
    src/UI/viewpage.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

#include(./QXlsx/QXlsx.pri)

DISTFILES += \
    libs/customplot/qucstomplot.pri \
    libs/xlsx/QXlsx.pri
