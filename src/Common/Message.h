#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QMessageBox>
#include <QToolTip>
#include <QPalette>

class Message : public QMessageBox
{
public:
    Message();
    virtual int sendMessage(const QString &title, const QString &text) = 0;
};

class InfoMessage: public Message
{
public:
    static InfoMessage* getInstance();
    InfoMessage();
    int sendMessage(const QString &title, const QString &text);
};

class ErrMessage: public Message
{
public:
    static ErrMessage *getInstance();
    ErrMessage();
    int sendMessage(const QString &title, const QString &text);
};

class WarnMessage: public Message
{
public:
    static WarnMessage *getInstance();
    WarnMessage();
    int sendMessage(const QString &title, const QString &text);
};

class QuestionMessage: public Message
{
public:
    static QuestionMessage* getInstance();
    QuestionMessage();
    int sendMessage(const QString &title, const QString &text);
};


#endif // MESSAGE_H
