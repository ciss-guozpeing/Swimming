#ifndef WINDOW_H
#define WINDOW_H

#include <QObject>
#include <QMap>
#include "mainwindow.h"

class Window : public QObject
{
    Q_OBJECT
private:

public:
    static Window* getInstalce();
    explicit Window(QMainWindow *parent = nullptr);

    QMap<QString,int> getMainWindowSize();
signals:

};

#endif // WINDOW_H
