#ifndef BASE_H
#define BASE_H

#include <QSettings>
#include <QFileInfo>
#include <QTextCodec>
#include <QCoreApplication>

class Base: public QSettings
{
private:
    QSettings* m_basicSettings;
    QSettings* m_userSettings;
    void _userSettings();
public:
    Base();
    void writeSettings();
    void readSettings();

};

#endif // BASE_H
