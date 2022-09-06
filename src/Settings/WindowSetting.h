#ifndef WINDOWSETTING_H
#define WINDOWSETTING_H

#include <QPoint>
#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QObject>
#include <QStyleFactory>
#include <QSettings>

class WindowSetting: public QObject
{
    QSettings* m_windowSetting;
public:
    static WindowSetting *getInstance();
    WindowSetting();
    ~WindowSetting();

    void setSupperUser();
    bool isExistsSupperUser();
    void configureDarkUi();
};

#endif // WINDOWSETTING_H
